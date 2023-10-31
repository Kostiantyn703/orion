#include "render_module.h"

#include <vector>

#include "SDL.h"
#include "glad/glad.h"

#include "shader.h"
#include "globals.h"

#define log_error	if (SDL_GetError()[0]) {SDL_LogError(0, SDL_GetError()); }

render_module::render_module() : is_wireframe(false)
{
	SDL_InitSubSystem(SDL_INIT_VIDEO);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	log_error;
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	log_error;
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	log_error;

	m_window = std::make_unique<window>();
}

render_module::~render_module() {
	m_renderables.clear();
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
}

void render_module::run(resource_module &in_resources) {
	glPolygonMode(GL_FRONT_AND_BACK, is_wireframe ? GL_LINE : GL_FILL);

	glClearColor(0.5f, 0.5f, 0.6f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT);

	shader_program *curr_shader = in_resources.get_shader(SPRITE_NAME);
	for (renderables::const_iterator it = m_renderables.cbegin(); it != m_renderables.cend(); ++it) {
		curr_shader->use();
		(*it)->draw(*curr_shader);
		m_vertex_array->bind();
		glDrawArrays(GL_LINES, 0, 6);
		m_vertex_array->unbind();
	}
	m_window->swap();
}

void render_module::add_object(renderable *in_obj) {
	m_renderables.push_back(in_obj);
}
