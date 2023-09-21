#include <iostream>
#include <string>
#include <vector>

#include "SDL_log.h"
#include "SDL_video.h"
#include "SDL_events.h"
#include "SDL.h"
#include <memory>
#include "window.h"

bool is_active = true;

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
		
		SDL_Rect bounds;
		SDL_GetDisplayBounds(i, &bounds);
		SDL_Log("Bounds\n\tx [%d]\ty [%d]\th [%d]\tw [%d]", bounds.x, bounds.y, bounds.h, bounds.w);
		
		SDL_Rect ubounds;
		SDL_GetDisplayUsableBounds(i, &ubounds);
		SDL_Log("Usable Bounds\n\tx [%d]\ty [%d]\th [%d]\tw [%d]", ubounds.x, ubounds.y, ubounds.h, ubounds.w);

		// enum
		SDL_DisplayOrientation display_orient =  SDL_GetDisplayOrientation(i);

		SDL_DisplayMode mode;
		SDL_GetCurrentDisplayMode(i, &mode);
		SDL_Log("Current Mode Info: format[%d] w [%d] h [%d] refresh_rate [%d]", mode.format, mode.w, mode.h, mode.refresh_rate);
	}
}

void handle_input() {
	SDL_Event curr_event;
	SDL_PollEvent(&curr_event);
	if (curr_event.type == SDL_KEYDOWN) {
		is_active = false;
	}
}

void update() {}
void render() {}

int main(int argc, char* args[]) {
	print_video_info();
	std::unique_ptr<window> main_window = std::make_unique<window>();
	
	SDL_Init(SDL_INIT_VIDEO);
	while (is_active) {
		handle_input();
		update();
		render();
	}

	return 0;
}