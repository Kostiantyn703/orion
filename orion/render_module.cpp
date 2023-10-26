#include "render_module.h"

#include <vector>
#include <complex>

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
	m_objects.clear();
}

void render_module::init() {
	
	m_vertex_array = std::make_unique<vertex_array>();
	m_vertex_array->bind();

	m_vertex_buffer = std::make_unique<buffer_object>(GL_ARRAY_BUFFER);
	m_element_buffer = std::make_unique<buffer_object>(GL_ELEMENT_ARRAY_BUFFER);

	m_vertex_buffer->init_data(vertices);
	m_element_buffer->init_data(indices);

	m_vertex_array->bind();
	m_vertex_array->init_data();
	
	m_vertex_buffer->unbind();
	m_element_buffer->unbind();
}

void render_module::run(resource_module &in_resources) {
	glPolygonMode(GL_FRONT_AND_BACK, is_wireframe ? GL_LINE : GL_FILL);

	glClearColor(0.5f, 0.5f, 0.6f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT);

	for (renderables::const_iterator it = m_objects.cbegin(); it != m_objects.cend(); ++it) {
		(*it)->draw(*in_resources.get_shader(SPRITE_SHADER_NAME));
		m_vertex_array->bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}
	m_window->swap();
}

void render_module::add_object(renderable *in_obj) {
	m_objects.push_back(in_obj);
}

//void render_module::add_objects(std::vector<renderable*> &in_obj_vec, resource_module &in_resources) {
//	m_objects.reserve(in_obj_vec.size());
//	m_objects.assign(in_obj_vec.begin(), in_obj_vec.end());
//
//	std::string vert_source;
//	in_resources.get_shader_source("vert", vert_source);
//	std::string frag_source;
//	in_resources.get_shader_source("frag", frag_source);
//	for (renderables::const_iterator it = m_objects.begin(); it != m_objects.end(); ++it) {
//		(*it)->init_shader(vert_source, frag_source);
//		(*it)->set_texture(*in_resources.get_texture("ship"));
//	}
//}
