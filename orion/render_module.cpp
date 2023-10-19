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
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	log_error;

	init();
}

render_module::~render_module() {
	m_a_objects.clear();
}

void render_module::init() {
	m_window = std::make_unique<window>();
}

void render_module::run() {
	glPolygonMode(GL_FRONT_AND_BACK, is_wireframe ? GL_LINE : GL_FILL);

	glClearColor(0.5f, 0.5f, 0.6f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT);

	for (render_objects::const_iterator it = m_a_objects.cbegin(); it != m_a_objects.cend(); ++it) {
		(*it)->draw();
	}

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	m_window->swap();
}