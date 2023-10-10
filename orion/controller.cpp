#include "controller.h"

#include "SDL_events.h"
#include "SDL_log.h"

#include "application.h"

controller::controller() {}

controller::~controller() {}

void controller::handle_input(application &in_app) {
	SDL_Event curr_event;
	SDL_PollEvent(&curr_event);

	if (curr_event.key.type != SDL_KEYUP) {
		return;
	}
	if (curr_event.key.keysym.sym == SDLK_UP) {
		SDL_Log("Key UP pressed");
	}
	if (curr_event.key.keysym.sym == SDLK_DOWN) {
		SDL_Log("Key DOWN pressed");
	}
	if (curr_event.key.keysym.sym == SDLK_LEFT) {
		SDL_Log("Key LEFT pressed");
	}
	if (curr_event.key.keysym.sym == SDLK_RIGHT) {
		SDL_Log("Key RIGHT pressed");
	}
	if (curr_event.key.keysym.sym == SDLK_ESCAPE) {
		in_app.set_active(false);
	}
	if (curr_event.key.keysym.sym == SDLK_1) {
		in_app.toggle_window_size();
	}
	if (curr_event.key.keysym.sym == SDLK_2) {
		in_app.toggle_wireframe();
	}
	if (curr_event.key.keysym.sym == SDLK_3) {
		in_app.print_video_info();
	}

}

