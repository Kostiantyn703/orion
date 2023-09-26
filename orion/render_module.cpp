#include "render_module.h"
#include "SDL.h"
#include "glad/glad.h"

#define log_error	if (SDL_GetError()[0]) {SDL_LogError(0, SDL_GetError()); }

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

	glClearColor(0.1f, 0.1f, 0.3f, 1.f);
	

	m_shader = std::make_unique<shader>();
	m_shader->compile();
}

void render_module::run() {
	glClear(GL_COLOR_BUFFER_BIT);
	m_shader->draw();
	m_window->swap();
}