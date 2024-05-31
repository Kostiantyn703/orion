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

background_renderer::background_renderer() : scroll_offset(0.f), scroll_speed(60.f) {}

void background_renderer::init() {
	set_texture(resource_module::get_instance()->get_texture(TEX_NAME_BACKGROUND));
	size.set_x((float)m_texture->get_width());
	size.set_y((float)m_texture->get_height());
}

void background_renderer::scroll(float delta_time) {
	scroll_offset += scroll_speed * delta_time;
}

void background_renderer::set_texture(texture *tex) {
	m_texture = tex;
}

void background_renderer::draw(const shader_program &shader) {
	glm::mat4 model = glm::mat4(1.f);
	glm::vec2 model_size(WINDOW_WIDTH, WINDOW_HEIGHT);
	model = glm::scale(model, glm::vec3(model_size, 1.f));
	glUniformMatrix4fv(glGetUniformLocation(shader.get_id(), "model"), 1, false, glm::value_ptr(model));

	float scalar_x = size.get_x() / WINDOW_WIDTH; 
	float scalar_y = size.get_y() / WINDOW_HEIGHT;
	glUniform2f(glGetUniformLocation(shader.get_id(), "scalar"), scalar_x, scalar_y);
	glUniform1f(glGetUniformLocation(shader.get_id(), "scroll"), scroll_offset / 50.f);

	glActiveTexture(GL_TEXTURE0);
	m_texture->bind();
}

text_render_module::text_render_module() : font_size(72), left_offset (120.f) {
	text_color = glm::vec3(0.4f, 0.6f, 1.f);
	init();
	load();
}

void text_render_module::init() {
	std::string vert_shader_source;
	if (!resource_module::get_instance()->load_shader(TEXT_ADDRESS_VERT, vert_shader_source)) {
		return;
	}
	std::string frag_shader_source;
	if (!resource_module::get_instance()->load_shader(TEXT_ADDRESS_FRAG, frag_shader_source)) {
		return;
	}
	
	std::unique_ptr<shader> vert = std::make_unique<shader>(vert_shader_source.data(), GL_VERTEX_SHADER);
	vert->compile();

	std::unique_ptr<shader> frag = std::make_unique<shader>(frag_shader_source.data(), GL_FRAGMENT_SHADER);
	frag->compile();

	shader_prog = std::make_unique<shader_program>();
	shader_prog->attach_shader(vert->get_id());
	shader_prog->attach_shader(frag->get_id());
	shader_prog->link();
	shader_prog->use();

	glm::mat4 projection = glm::ortho(0.f, WINDOW_WIDTH, WINDOW_HEIGHT, 0.f);
	glUniformMatrix4fv(glGetUniformLocation(shader_prog->get_id(), "projection"), 1, false, glm::value_ptr(projection));
	glUniform1i(glGetUniformLocation(shader_prog->get_id(), "text"), 0);

	vert->destroy();
	frag->destroy();

	glGenVertexArrays(1, &vert_array);
	glGenBuffers(1, &vert_buffer);
	glBindVertexArray(vert_array);
	glBindBuffer(GL_ARRAY_BUFFER, vert_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void text_render_module::draw_title() {
	draw("ORION", left_offset, WINDOW_HEIGHT / 2.f - 72.f, 1.75f);
	draw("Press \"Enter\" to start.", left_offset, WINDOW_HEIGHT / 2.f + 50.f, 0.25f);
}

void text_render_module::draw_score(const int score) {
	draw("Score:", left_offset, WINDOW_HEIGHT / 2.f - 72.f, 1.f);
	char buff[16];
	itoa(score, buff, 10);
	draw(buff, left_offset, WINDOW_HEIGHT / 2.f, 1.f);
}

void text_render_module::draw(const std::string &text, float x, float y, float scale) {
	// activate corresponding render state	
	shader_prog->use();
	glUniform3f(glGetUniformLocation(shader_prog->get_id(), "text_color"), text_color.x, text_color.y, text_color.z);
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(vert_array);

	// iterate through all characters
	std::string::const_iterator c;
	for (c = text.begin(); c != text.end(); c++)
	{
		character ch = characters[*c];

		float xpos = x + ch.bearing.x * scale;
		float ypos = y + (characters['H'].bearing.y - ch.bearing.y) * scale;

		float w = ch.size.x * scale;
		float h = ch.size.y * scale;
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
		glBindTexture(GL_TEXTURE_2D, ch.id);
		// update content of VBO memory
		glBindBuffer(GL_ARRAY_BUFFER, vert_buffer);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(verts), verts); // be sure to use glBufferSubData and not glBufferData
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		// render quad
		glDrawArrays(GL_TRIANGLES, 0, 6);
		// now advance cursors for next glyph
		x += (ch.advance >> 6) * scale; // bitshift by 6 to get value in pixels (1/64th times 2^6 = 64)
	}
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void text_render_module::load() {
	// first clear the previously loaded Characters
	characters.clear();
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
	FT_Set_Pixel_Sizes(face, 0, font_size);
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
		character ch = {
			texture,
			glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
			glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
			(unsigned int)face->glyph->advance.x
		};
		characters.insert(std::pair<char, character>(c, ch));
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

	window = std::make_unique<game_window>();

	init_shader(SPRITE_ADDRESS_VERT, SPRITE_ADDRESS_FRAG);
	//init_shader(DEBUG_ADDRESS_VERT, DEBUG_ADDRESS_FRAG);
}

void render_module::init() {
	vert_array = std::make_unique<vertex_array>();
	vert_buffer = std::make_unique<buffer_object>(GL_ARRAY_BUFFER);

	vert_buffer->bind();
	vert_buffer->init_data(vertices);

	vert_array->bind();
	vert_array->init_data();

	vert_buffer->unbind();
	vert_array->unbind();

	background.init();
	text_renderer = std::make_unique<text_render_module>();
}

void render_module::init_shader(const char *vert_address, const char *frag_address) {
	std::string vert_shader_source;
	if (!resource_module::get_instance()->load_shader(vert_address, vert_shader_source)) {
		return;
	}
	std::string frag_shader_source;
	if (!resource_module::get_instance()->load_shader(frag_address, frag_shader_source)) {
		return;
	}
	compile_shaders(vert_shader_source, frag_shader_source);
}

void render_module::compile_shaders(const std::string &vertex_source, const std::string &fragment_source) {
	std::unique_ptr<shader> vert = std::make_unique<shader>(vertex_source.data(), GL_VERTEX_SHADER);
	vert->compile();

	std::unique_ptr<shader> frag = std::make_unique<shader>(fragment_source.data(), GL_FRAGMENT_SHADER);
	frag->compile();

	shader_program sp;
	sp.attach_shader(vert->get_id());
	sp.attach_shader(frag->get_id());
	sp.link();
	sp.use();

	glm::mat4 projection = glm::ortho(0.f, WINDOW_WIDTH, WINDOW_HEIGHT, 0.f, -1.f, 1.f);
	glUniformMatrix4fv(glGetUniformLocation(sp.get_id(), "projection"), 1, false, glm::value_ptr(projection));
	shaders.push_back(std::make_unique<shader_program>(sp));

	vert->destroy();
	frag->destroy();
}

void render_module::run(world_module *world) {
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glClearColor(0.5f, 0.5f, 0.6f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT);

	for (int i = 0; i < shaders.size(); ++i) {
		shaders[i]->use();
		background.draw(*shaders[i]);
		vert_array->bind();
		glDrawArrays(GL_TRIANGLES, 0, 6);
		vert_array->unbind();
		for (int j = 0; j < world->objects.size(); ++j) {
			world->objects[j]->draw(*shaders[i]);
			vert_array->bind();
			glDrawArrays(GL_TRIANGLES, 0, 6);
			vert_array->unbind();
		}
	}

	if (world->should_show_title()) {
		text_renderer->draw_title();
	}
	if (world->get_show_score()) {
		text_renderer->draw_score((int)world->get_score());
	}

	window->swap();
}

void render_module::scroll_background(float delta_time) {
	background.scroll(delta_time);
}
