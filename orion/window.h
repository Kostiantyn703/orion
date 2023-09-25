#ifndef WINDOW_H
#define WINDOW_H

#include "SDL_video.h"

class shader;

class window {
public:
	window();
	~window();

	void init_gl();

	void render(const shader &in_shader);

	void log_info();

	void toggle_fullscreen();

private:
	SDL_Window *m_window;
	SDL_GLContext m_context;
};
#endif WINDOW_H
