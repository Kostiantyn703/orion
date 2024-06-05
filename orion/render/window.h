#ifndef WINDOW_H
#define WINDOW_H

#include "SDL_video.h"

class game_window {
public:
	game_window();
	~game_window();

	void swap();

private:
	SDL_Window *window;
	SDL_GLContext context;
};
#endif WINDOW_H
