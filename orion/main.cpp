#include <iostream>
#include <string>
#include <vector>

#include "SDL_log.h"
#include "SDL_video.h"

constexpr int WINDOW_HEIGHT = 600;
constexpr int WINDOW_WIDTH = 800;

void print_video_info() {
	int drivers_num = SDL_GetNumVideoDrivers();
	SDL_Log("Num of drivers is %d", drivers_num);

	for (int i = 0; i < drivers_num; ++i) {
		SDL_Log("Driver %d [%s]", i, SDL_GetVideoDriver(i));
	}
	SDL_Log("Current driver [%s]", SDL_GetCurrentVideoDriver());

	int num_displays = SDL_GetNumVideoDisplays();
	SDL_Log("Displays quantity [%d]", num_displays);
	for (int i = 0; i < num_displays; ++i) {
		SDL_Log("Display %d [%s]", i, SDL_GetDisplayName(i));
	}
}

int main() {
	SDL_Window *window = SDL_CreateWindow	(		"PROJECT ORION"
											,	SDL_WINDOWPOS_CENTERED
											,	SDL_WINDOWPOS_CENTERED
											,	WINDOW_WIDTH
											,	WINDOW_HEIGHT
											, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE
	);

	print_video_info();

	return 0;
}