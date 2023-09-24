#include "window.h"

#include "SDL_video.h"
#include "SDL_log.h"
#include "SDL_OpenGL.h"
#include "SDL.h"

constexpr int	WINDOW_HEIGHT		= 600;
constexpr int	WINDOW_WIDTH		= 800;
const char		*WINDOW_NAME		= "PROJECT ORION";

#define log_error	if (SDL_GetError()[0]) {SDL_LogError(0, SDL_GetError()); }

window::window() {
	init_gl();
	Uint32 flags = SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL;
	m_window = SDL_CreateWindow	(	WINDOW_NAME
								,	SDL_WINDOWPOS_CENTERED
								,	SDL_WINDOWPOS_CENTERED
								,	WINDOW_WIDTH
								,	WINDOW_HEIGHT
								,	flags
								);

	m_context = SDL_GL_CreateContext(m_window);
	
	log_error;
}

window::~window() {
	SDL_GL_DeleteContext(m_context);
	SDL_DestroyWindow(m_window);
	log_error;
}

void window::init_gl() {
	SDL_InitSubSystem(SDL_INIT_VIDEO);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	log_error;
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	log_error;
}

void window::render() {
	glClearColor(0.5f, 0.1f, 0.2f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT);
	SDL_GL_SwapWindow(m_window);
}

void window::log_info() {
	if (!m_window) {
		SDL_LogError(0, "Window has not been initialized");
		return;
	}
}

void window::toggle_fullscreen() {
	int display_idx = SDL_GetWindowDisplayIndex(m_window);
	SDL_Rect display_bounds;
	SDL_GetDisplayBounds(display_idx, &display_bounds);
	
	int window_width		= 0;
	int window_height		= 0;
	SDL_GetWindowSize(m_window, &window_width, &window_height);

	if (display_bounds.h != window_height && display_bounds.w != window_width) {
		SDL_SetWindowFullscreen(m_window, SDL_WINDOW_FULLSCREEN_DESKTOP);
	}
	if (display_bounds.h == window_height && display_bounds.w == window_width) {
		SDL_SetWindowFullscreen(m_window, 0);
	}
}
