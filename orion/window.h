#ifndef WINDOW_H
#define WINDOW_H

#include "SDL_video.h"

class window {
public:
	window();
	~window();

	void swap();

	void log_info();

	void toggle_fullscreen();

private:
	SDL_Window *m_window;
	SDL_GLContext m_context;
};
#endif WINDOW_H
