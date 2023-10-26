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

	init();
}

render_module::~render_module() {
	m_objects.clear();
}

void render_module::init() {
	m_window = std::make_unique<window>();
	m_vertex_array = std::make_unique<vertex_array>();
}

void render_module::run() {
	glPolygonMode(GL_FRONT_AND_BACK, is_wireframe ? GL_LINE : GL_FILL);

	glClearColor(0.5f, 0.5f, 0.6f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT);

	for (renderables::const_iterator it = m_objects.cbegin(); it != m_objects.cend(); ++it) {
		(*it)->draw();
	}
	m_vertex_array->bind();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	m_window->swap();
}

void render_module::add_object(renderable *in_obj, resource_module &in_resources) {
	m_objects.push_back(in_obj);
	std::string vert_source;
	in_resources.get_shader_source("vert", vert_source);
	std::string frag_source;
	in_resources.get_shader_source("frag", frag_source);
	
	m_vertex_array->bind();
	
	m_objects.back()->init(vert_source, frag_source);
	m_vertex_array->init_data();

	m_objects.back()->set_texture(*in_resources.get_texture("ship"));
}

void render_module::add_objects(std::vector<renderable*> &in_obj_vec, resource_module &in_resources) {
	m_objects.reserve(in_obj_vec.size());
	m_objects.assign(in_obj_vec.begin(), in_obj_vec.end());

	std::string vert_source;
	in_resources.get_shader_source("vert", vert_source);
	std::string frag_source;
	in_resources.get_shader_source("frag", frag_source);
	for (renderables::const_iterator it = m_objects.begin(); it != m_objects.end(); ++it) {
		(*it)->init(vert_source, frag_source);
		(*it)->set_texture(*in_resources.get_texture("ship"));
	}
}
