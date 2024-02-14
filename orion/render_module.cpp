#include "render_module.h"

#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

#include "SDL.h"
#include "glad/glad.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "shader.h"
#include "globals.h"
#include "resource_module.h"

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
	// TODO: change order, made for test
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

	// TODO: temporary
	m_background.init();
}

void render_module::init_shader(const char *in_vert_address, const char *in_frag_address) {
	std::string v_shader_source;
	if (!load_shader(in_vert_address, v_shader_source)) {
		return;
	}
	std::string f_shader_source;
	if (!load_shader(in_frag_address, f_shader_source)) {
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

bool render_module::load_shader(const char *source_address, std::string &out_shader_source) {
	std::ifstream read_stream(source_address);
	if (!read_stream.is_open()) {
		SDL_LogError(0, "Shader source was failed to load from file.\nFile address [%s]", source_address);
		return false;
	}

	std::stringstream str_stream;
	str_stream << read_stream.rdbuf();
	out_shader_source = str_stream.str();
	if (out_shader_source.empty()) {
		SDL_LogError(0, "Shader source code was empty.");
		return false;
	}
	return true;
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
	m_window->swap();
}
