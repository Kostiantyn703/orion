#include "window.h"

#include "SDL_video.h"
#include "SDL_log.h"
#include "SDL.h"

#include "glad/glad.h"
#include "globals.h"
#include <SDL_opengl.h>

#define log_error	if (SDL_GetError()[0]) {SDL_LogError(0, SDL_GetError()); }

window::window() {
	unsigned int flags = SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL;
	m_window = SDL_CreateWindow	(	GAME_NAME
								,	SDL_WINDOWPOS_CENTERED
								,	SDL_WINDOWPOS_CENTERED
								,	(int)WINDOW_WIDTH
								,	(int)WINDOW_HEIGHT
								,	flags
								);
	m_context = SDL_GL_CreateContext(m_window);
	gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_PROGRAM_POINT_SIZE);

	log_error;
}

window::~window() {
	SDL_GL_DeleteContext(m_context);
	SDL_DestroyWindow(m_window);
	log_error;
}

void window::swap() {
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
