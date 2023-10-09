#include "glad/glad.h"

#include "SDL_log.h"
#include "SDL_video.h"
#include "SDL_events.h"
#include "SDL.h"

#include <memory>

#include "render_module.h"
#include "controller.h"

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
		//SDL_GetCurrentDisplayMode(i, &mode);
		//SDL_Log("Current Mode Info: format[%d] w [%d] h [%d] refresh_rate [%d]", mode.format, mode.w, mode.h, mode.refresh_rate);
		
		SDL_GetDesktopDisplayMode(i, &mode);
		SDL_Log("Current Mode Info: format[%d] w [%d] h [%d] refresh_rate [%d]", mode.format, mode.w, mode.h, mode.refresh_rate);
	}
}

void handle_input() {//window &in_window) {
	SDL_Event curr_event;
	SDL_PollEvent(&curr_event);

	if (curr_event.key.type != SDL_KEYUP) {
		return;
	}

	if (curr_event.key.keysym.sym == SDLK_ESCAPE) {
		is_active = false;
	}
	if (curr_event.key.keysym.sym == SDLK_1) {
		//in_window.toggle_fullscreen();
	}
	if (curr_event.key.keysym.sym == SDLK_2) {
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
}

void update() {}


int main(int argc, char* args[]) {
	//print_video_info();
	std::unique_ptr<render_module> renderer = std::make_unique<render_module>();
	std::unique_ptr<controller> input_handler = std::make_unique<controller>();
	while (is_active) {
		input_handler->handle_input(is_active);
		update();
		renderer->run();
	}

	return 0;
}