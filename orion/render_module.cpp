#include "render_module.h"

#include <vector>
#include <complex>

#include "SDL.h"
#include "glad/glad.h"

#include "shader.h"
#include "globals.h"

#define log_error	if (SDL_GetError()[0]) {SDL_LogError(0, SDL_GetError()); }

render_module::render_module() {
	SDL_InitSubSystem(SDL_INIT_VIDEO);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	log_error;
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	log_error;
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	log_error;
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	log_error;

	init();
}

render_module::~render_module() {}

void render_module::init() {
	m_window = std::make_unique<window>();
	m_resources = std::make_unique<resource_module>();
	std::string shader_source_buffer;
	m_resources->get_shader_source("vert", shader_source_buffer);
	std::unique_ptr<shader> vert = std::make_unique<shader>(shader_source_buffer.data(), GL_VERTEX_SHADER);
	vert->compile();
	
	shader_source_buffer.clear();
	m_resources->get_shader_source("frag", shader_source_buffer);
	std::unique_ptr<shader> frag = std::make_unique<shader>(shader_source_buffer.data(), GL_FRAGMENT_SHADER);
	frag->compile();

	m_shader_program = std::make_unique<shader_program>();
	m_shader_program->attach_shader(vert->get_id());
	m_shader_program->attach_shader(frag->get_id());
	m_shader_program->link();

	vert->destroy();
	frag->destroy();

	m_vertex_array = std::make_unique<vertex_array>();
	m_vertex_buffer = std::make_unique<buffer_object>(GL_ARRAY_BUFFER);
	m_element_buffer = std::make_unique<buffer_object>(GL_ELEMENT_ARRAY_BUFFER);

	m_vertex_array->bind();

	m_vertex_buffer->init_data(vertices);
	m_element_buffer->init_data(indices);
	m_vertex_array->init_data();
	
	m_texture = std::make_unique<texture>();
	
	GLint width, height, nr_channels;
	unsigned char *texture_data = m_resources->load_texture(width, height, nr_channels);
	m_texture->init_data(texture_data, width, height, nr_channels);
	m_resources->free_texture_data(texture_data);

	m_vertex_buffer->unbind();
	m_vertex_array->unbind();

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void render_module::run() {
	glClearColor(0.5f, 0.5f, 0.6f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT);

	m_texture->bind();
	m_shader_program->use();
	m_vertex_array->bind();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	m_window->swap();
}