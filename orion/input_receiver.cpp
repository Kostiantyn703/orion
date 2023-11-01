#include "input_receiver.h"
#include <SDL_events.h>
#include <SDL_log.h>

input_receiver::input_receiver() {}
input_receiver::~input_receiver() {}

void input_receiver::receive_key() {

	SDL_Event curr_event;
	SDL_PollEvent(&curr_event);
	switch (curr_event.key.keysym.sym) {
	case SDLK_w:
	case SDLK_UP:
		if (curr_event.key.type & SDL_KEYDOWN && (curr_event.key.state | SDL_PRESSED) ) {
			SDL_Log("[UP]");
		}
		break;
	case SDLK_d:
	case SDLK_RIGHT:
		if (curr_event.key.state & SDL_PRESSED) break;
		SDL_Log("[RIGHT]");
		break;
	case SDLK_s:
	case SDLK_DOWN:
		if (curr_event.key.state & SDL_PRESSED) break;
		SDL_Log("[DOWN]");
		break;
	case SDLK_a:
	case SDLK_LEFT:
		if (curr_event.key.state & SDL_PRESSED) break;
		SDL_Log("[LEFT]");
		break;
	}
}
