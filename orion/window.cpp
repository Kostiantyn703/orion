#include "window.h"

#include "SDL_video.h"
#include "SDL_log.h"

constexpr int	WINDOW_HEIGHT		= 600;
constexpr int	WINDOW_WIDTH		= 800;
const char		*WINDOW_NAME		= "PROJECT ORION";

#define log_error	if (SDL_GetError()[0]) {SDL_LogError(0, SDL_GetError()); }

window::window() {
	m_flags = SDL_WINDOW_ALWAYS_ON_TOP | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL;
	m_window = SDL_CreateWindow	(	WINDOW_NAME
								,	SDL_WINDOWPOS_CENTERED
								,	SDL_WINDOWPOS_CENTERED
								,	WINDOW_WIDTH
								,	WINDOW_HEIGHT
								,	m_flags
								);

	m_context = SDL_GL_CreateContext(m_window);
	
	log_error;
}

window::~window() {
	SDL_GL_DeleteContext(m_context);
	SDL_DestroyWindow(m_window);

	log_error;
}

void window::log_info() {
	

}
