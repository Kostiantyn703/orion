#include "render_module.h"

#include "SDL.h"
#include "glad/glad.h"

#include "shader.h"
#include <vector>

#define log_error	if (SDL_GetError()[0]) {SDL_LogError(0, SDL_GetError()); }

const char *vertexShaderSource;
const char *fragmentShaderSource;

std::vector<GLfloat> vertices = {
	0.5f,	0.5f,
	0.5f,	-0.5f,
	-0.5f,	-0.5f,
	-0.5f,	0.5f
};

std::vector<unsigned int> indices = { 
	0, 1, 2,
	0, 2, 3
};

render_module::render_module() {
	init();
}

render_module::~render_module() {}

void render_module::init() {
	SDL_InitSubSystem(SDL_INIT_VIDEO);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	log_error;
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	log_error;

	m_window = std::make_unique<window>();
	
	std::unique_ptr<shader> vert = std::make_unique<shader>(vertexShaderSource, GL_VERTEX_SHADER);
	vert->compile();
	std::unique_ptr<shader> frag = std::make_unique<shader>(fragmentShaderSource, GL_FRAGMENT_SHADER);
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
	
	m_vertex_buffer->unbind();
	m_vertex_array->unbind();

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void render_module::run() {
	glClearColor(0.1f, 0.1f, 0.3f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT);
	m_shader_program->use();
	m_vertex_array->bind();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	m_window->swap();
}