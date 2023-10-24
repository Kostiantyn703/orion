#include "controller.h"

#include "SDL_events.h"
#include "SDL_log.h"

#include "application.h"

controller::controller() {}

controller::~controller() {}

void controller::handle_input(application &in_app) {
	SDL_Event curr_event;
	SDL_PollEvent(&curr_event);

	if (curr_event.key.type == SDL_KEYUP) {
		//in_app.get_game_object()->set_direction(direction::D_NONE);
		return;
	}
	SDL_Keycode curr_key = curr_event.key.keysym.sym;
	// game object controls
	if ((curr_key == SDLK_UP) || (curr_key == SDLK_w)) {
		//in_app.get_game_object()->set_direction(direction::D_UP);
		return;
	}
	if ((curr_key == SDLK_DOWN) || (curr_key == SDLK_s)) {
		//in_app.get_game_object()->set_direction(direction::D_DOWN);
		return;
	}
	if ((curr_key == SDLK_LEFT) || (curr_key == SDLK_a)) {
		//in_app.get_game_object()->set_direction(direction::D_LEFT);
		return;
	}
	if ((curr_key == SDLK_RIGHT) || (curr_key == SDLK_d)) {
		//in_app.get_game_object()->set_direction(direction::D_RIGHT);
		return;
	}

	// system controls
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
	if (curr_event.key.keysym.sym == SDLK_4) {
		in_app.show_current_time();
	}
}

