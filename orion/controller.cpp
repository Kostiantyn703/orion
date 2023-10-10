#include "controller.h"
#include <SDL_events.h>
#include <SDL_log.h>

controller::controller() {

}

controller::~controller() {

}

void controller::handle_input(bool &out_active) {
	SDL_Event curr_event;
	SDL_PollEvent(&curr_event);

	if (curr_event.key.type == SDL_KEYUP) {
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
		out_active = false;
	}
	if (curr_event.key.keysym.sym == SDLK_1) {
		//in_window.toggle_fullscreen();
	}
	if (curr_event.key.keysym.sym == SDLK_2) {
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}

}

