#pragma warning(disable : 4996)
#include "render_module.h"

#include <SDL.h>
#include <stdlib.h>

#include <ft2build.h>
#include <freetype/freetype.h>

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "../utils/globals.h"
#include "../modules/resource_module.h"

#include "shader.h"

#define log_error	if (SDL_GetError()[0]) {SDL_LogError(0, SDL_GetError()); }

void background::init() {
	m_texture = resource_module::get_instance()->get_texture(TEX_NAME_BACKGROUND);
	m_size.set_x((float)m_texture->get_width());
	m_size.set_y((float)m_texture->get_height());
}

void background::draw(const shader_program &in_shader) {
	// draw texture
	glm::mat4 model = glm::mat4(1.f);
	glm::vec2 model_size(WINDOW_WIDTH, WINDOW_HEIGHT);
	model = glm::scale(model, glm::vec3(model_size, 1.f));
	glUniformMatrix4fv(glGetUniformLocation(in_shader.id(), "model"), 1, false, glm::value_ptr(model));

	float scalar_x = m_size.get_x() / WINDOW_WIDTH; 
	float scalar_y = m_size.get_y() / WINDOW_HEIGHT;
	glUniform2f(glGetUniformLocation(in_shader.id(), "scalar"), scalar_x, scalar_y);
	glUniform1f(glGetUniformLocation(in_shader.id(), "scroll"), m_scroll_offset / 50.f);

	glActiveTexture(GL_TEXTURE0);
	m_texture->bind();
}

text_render_module::text_render_module() {
	m_text_color = glm::vec3(0.4f, 0.6f, 1.f);
	m_font_size = 72;
	m_left_offset = 120.f;
	init();
	load();
}

text_render_module::~text_render_module() {}

void text_render_module::init() {
	std::string v_shader_source;
	if (!resource_module::get_instance()->load_shader(TEXT_ADDRESS_VERT, v_shader_source)) {
		return;
	}
	std::string f_shader_source;
	if (!resource_module::get_instance()->load_shader(TEXT_ADDRESS_FRAG, f_shader_source)) {
		return;
	}
	
	std::unique_ptr<shader> vert = std::make_unique<shader>(v_shader_source.data(), GL_VERTEX_SHADER);
	vert->compile();

	std::unique_ptr<shader> frag = std::make_unique<shader>(f_shader_source.data(), GL_FRAGMENT_SHADER);
	frag->compile();

	m_shader = std::make_unique<shader_program>();
	m_shader->attach_shader(vert->get_id());
	m_shader->attach_shader(frag->get_id());
	m_shader->link();
	m_shader->use();

	glm::mat4 projection = glm::ortho(0.f, WINDOW_WIDTH, WINDOW_HEIGHT, 0.f);
	glUniformMatrix4fv(glGetUniformLocation(m_shader->id(), "projection"), 1, false, glm::value_ptr(projection));
	glUniform1i(glGetUniformLocation(m_shader->id(), "text"), 0);

	vert->destroy();
	frag->destroy();

	glGenVertexArrays(1, &m_vertex_array);
	glGenBuffers(1, &m_vertex_buffer);
	glBindVertexArray(m_vertex_array);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertex_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void text_render_module::draw_title() {
	draw("ORION", m_left_offset, WINDOW_HEIGHT / 2.f - 72.f, 1.75f);
	draw("Press \"Enter\" to start.", m_left_offset, WINDOW_HEIGHT / 2.f + 50.f, 0.25f);
}

void text_render_module::draw_score(const int in_score) {
	draw("Score:", m_left_offset, WINDOW_HEIGHT / 2.f - 72.f, 1.f);
	char buff[16];
	itoa(in_score, buff, 10);
	draw(buff, m_left_offset, WINDOW_HEIGHT / 2.f, 1.f);
}

void text_render_module::draw(const std::string &in_text, float in_x, float in_y, float in_scale) {
	// activate corresponding render state	
	m_shader->use();
	glUniform3f(glGetUniformLocation(m_shader->id(), "text_color"), m_text_color.x, m_text_color.y, m_text_color.z);
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(m_vertex_array);

	// iterate through all characters
	std::string::const_iterator c;
	for (c = in_text.begin(); c != in_text.end(); c++)
	{
		character ch = m_characters[*c];

		float xpos = in_x + ch.m_bearing.x * in_scale;
		float ypos = in_y + (m_characters['H'].m_bearing.y - ch.m_bearing.y) * in_scale;

		float w = ch.m_size.x * in_scale;
		float h = ch.m_size.y * in_scale;
		// update VBO for each character
		float verts[6][4] = {
			{ xpos,     ypos + h,   0.0f, 1.0f },
			{ xpos + w, ypos,       1.0f, 0.0f },
			{ xpos,     ypos,       0.0f, 0.0f },

			{ xpos,     ypos + h,   0.0f, 1.0f },
			{ xpos + w, ypos + h,   1.0f, 1.0f },
			{ xpos + w, ypos,       1.0f, 0.0f }
		};
		// render glyph texture over quad
		glBindTexture(GL_TEXTURE_2D, ch.m_id);
		// update content of VBO memory
		glBindBuffer(GL_ARRAY_BUFFER, m_vertex_buffer);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(verts), verts); // be sure to use glBufferSubData and not glBufferData
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		// render quad
		glDrawArrays(GL_TRIANGLES, 0, 6);
		// now advance cursors for next glyph
		in_x += (ch.m_advance >> 6) * in_scale; // bitshift by 6 to get value in pixels (1/64th times 2^6 = 64)
	}
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void text_render_module::load() {
	// first clear the previously loaded Characters
	m_characters.clear();
	// then initialize and load the FreeType library
	FT_Library ft;
	if (FT_Init_FreeType(&ft)) {		// all functions return a value different than 0 whenever an error occurred
		SDL_Log("Could not init FreeType Library");
	}
	// load font as face
	FT_Face face;
	if (FT_New_Face(ft, FONT_PATH, 0, &face)) {
		SDL_Log("ERROR::FREETYPE: Failed to load font");
	}
	// set size to load glyphs as
	FT_Set_Pixel_Sizes(face, 0, m_font_size);
	// disable byte-alignment restriction
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	// then for the first 128 ASCII characters, pre-load/compile their characters and store them
	for (GLubyte c = 0; c < 128; c++) // lol see what I did there 
	{
		// load character glyph 
		if (FT_Load_Char(face, c, FT_LOAD_RENDER))
		{
			SDL_Log( "ERROR::FREETYTPE: Failed to load Glyph");
			continue;
		}
		// generate texture
		unsigned int texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RED,
			face->glyph->bitmap.width,
			face->glyph->bitmap.rows,
			0,
			GL_RED,
			GL_UNSIGNED_BYTE,
			face->glyph->bitmap.buffer
		);
		// set texture options
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// now store character for later use
		character curr_char = {
			texture,
			glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
			glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
			(unsigned int)face->glyph->advance.x
		};
		m_characters.insert(std::pair<char, character>(c, curr_char));
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	// destroy FreeType once we're finished
	FT_Done_Face(face);
	FT_Done_FreeType(ft);
}

render_module::render_module()
{
	SDL_InitSubSystem(SDL_INIT_VIDEO);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	log_error;
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	log_error;
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	log_error;

	m_window = std::make_unique<window>();

	init_shader(SPRITE_ADDRESS_VERT, SPRITE_ADDRESS_FRAG);
	//init_shader(DEBUG_ADDRESS_VERT, DEBUG_ADDRESS_FRAG);
}

void render_module::init() {
	m_vertex_array = std::make_unique<vertex_array>();
	m_vertex_buffer = std::make_unique<buffer_object>(GL_ARRAY_BUFFER);

	m_vertex_buffer->bind();
	m_vertex_buffer->init_data(vertices);

	m_vertex_array->bind();
	m_vertex_array->init_data();

	m_vertex_buffer->unbind();
	m_vertex_array->unbind();

	m_background.init();
	m_text_renderer = std::make_unique<text_render_module>();
}

void render_module::init_shader(const char *in_vert_address, const char *in_frag_address) {
	std::string v_shader_source;
	if (!resource_module::get_instance()->load_shader(in_vert_address, v_shader_source)) {
		return;
	}
	std::string f_shader_source;
	if (!resource_module::get_instance()->load_shader(in_frag_address, f_shader_source)) {
		return;
	}
	compile_shaders(v_shader_source, f_shader_source);
}

void render_module::compile_shaders(const std::string &in_vertex_source, const std::string &in_fragment_source) {
	std::unique_ptr<shader> vert = std::make_unique<shader>(in_vertex_source.data(), GL_VERTEX_SHADER);
	vert->compile();

	std::unique_ptr<shader> frag = std::make_unique<shader>(in_fragment_source.data(), GL_FRAGMENT_SHADER);
	frag->compile();

	shader_program curr_shader;
	curr_shader.attach_shader(vert->get_id());
	curr_shader.attach_shader(frag->get_id());
	curr_shader.link();
	curr_shader.use();

	glm::mat4 projection = glm::ortho(0.f, WINDOW_WIDTH, WINDOW_HEIGHT, 0.f, -1.f, 1.f);
	glUniformMatrix4fv(glGetUniformLocation(curr_shader.id(), "projection"), 1, false, glm::value_ptr(projection));
	m_shaders.push_back(std::make_unique<shader_program>(curr_shader));

	vert->destroy();
	frag->destroy();
}

void render_module::run(world_module *in_world) {
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glClearColor(0.5f, 0.5f, 0.6f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT);

	for (int i = 0; i < m_shaders.size(); ++i) {
		m_shaders[i]->use();
		m_background.draw(*m_shaders[i]);
		m_vertex_array->bind();
		glDrawArrays(GL_TRIANGLES, 0, 6);
		m_vertex_array->unbind();
		for (int j = 0; j < in_world->m_objects.size(); ++j) {
			in_world->m_objects[j]->draw(*m_shaders[i]);
			m_vertex_array->bind();
			glDrawArrays(GL_TRIANGLES, 0, 6);
			m_vertex_array->unbind();
		}
	}

	if (in_world->get_show_title()) {
		m_text_renderer->draw_title();
	}
	if (in_world->get_show_score()) {
		m_text_renderer->draw_score((int)in_world->get_score());
	}

	m_window->swap();
}

void render_module::scroll_background(float delta_time) {
	float scroll_speed = 60.f;
	m_background.m_scroll_offset += delta_time * scroll_speed;
}
