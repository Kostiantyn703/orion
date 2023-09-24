#ifndef WINDOW_H
#define WINDOW_H

#include "SDL_video.h"

class window {
public:
	window();
	~window();

	void log_info();

	void toggle_fullscreen();

private:
	unsigned int m_flags;

	SDL_Window *m_window;
	SDL_GLContext m_context;
};
#endif WINDOW_H
