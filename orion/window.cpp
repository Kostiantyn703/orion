#include "window.h"

#include "SDL_video.h"

constexpr int	WINDOW_HEIGHT		= 600;
constexpr int	WINDOW_WIDTH		= 800;
const char		*WINDOW_NAME		= "PROJECT ORION";

window::window() {
	m_flags = SDL_WINDOW_ALWAYS_ON_TOP | SDL_WINDOW_RESIZABLE;
	m_window = SDL_CreateWindow	(	WINDOW_NAME
								,	SDL_WINDOWPOS_CENTERED
								,	SDL_WINDOWPOS_CENTERED
								,	WINDOW_WIDTH
								,	WINDOW_HEIGHT
								,	m_flags
								);
}

window::~window() {
	SDL_DestroyWindow(m_window);
}

