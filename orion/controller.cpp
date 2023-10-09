#include "controller.h"
#include <SDL_events.h>

controller::controller() {

}

controller::~controller() {

}

void controller::handle_input(bool &out_active) {
	SDL_Event curr_event;
	SDL_PollEvent(&curr_event);

	if (curr_event.key.type != SDL_KEYUP) {
		return;
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

