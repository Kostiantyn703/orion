#include "input_receiver.h"
#include <SDL_log.h>

void input_receiver::receive_key() {
	SDL_Event curr_event;
	SDL_PollEvent(&curr_event);

	handle_key_down(curr_event);
	handle_key_up(curr_event);
}

void input_receiver::handle_key_down(const SDL_Event &in_event) {
	if (in_event.type & SDL_KEYDOWN) {
		switch (in_event.key.keysym.sym) {
		case SDLK_UP:
			if (add_key(event_type::ET_UP, in_event.key.state)) {
				SDL_Log("[UP]");
			}
			break;
		case SDLK_RIGHT:
			if (add_key(event_type::ET_RIGHT, in_event.key.state)) {
				SDL_Log("[RIGHT]");
			}
			break;
		case SDLK_DOWN:
			if (add_key(event_type::ET_DOWN, in_event.key.state)) {
				SDL_Log("[DOWN]");
			}
			break;
		case SDLK_LEFT:
			if (add_key(event_type::ET_LEFT, in_event.key.state)) {
				SDL_Log("[LEFT]");
			}
			break;
		}
	}
}

void input_receiver::handle_key_up(const SDL_Event &in_event) {
	if (in_event.type & SDL_KEYUP) {
		switch (in_event.key.keysym.sym) {
		case SDLK_UP:
			if (remove_key(event_type::ET_UP, in_event.key.state)) {
				SDL_Log("[UP] released");
			}
			break;
		case SDLK_RIGHT:
			if (remove_key(event_type::ET_RIGHT, in_event.key.state)) {
				SDL_Log("[RIGHT] released");
			}
			break;
		case SDLK_DOWN:
			if (remove_key(event_type::ET_DOWN, in_event.key.state)) {
				SDL_Log("[DOWN] released");
			}
			break;
		case SDLK_LEFT:
			if (remove_key(event_type::ET_LEFT, in_event.key.state)) {
				SDL_Log("[LEFT] released");
			}
			break;
		}
	}
}

bool input_receiver::add_key(event_type in_type, char in_state) {
	events_map::const_iterator it = m_received_events.find(in_type);
	if (it == m_received_events.end()) {
		m_received_events.insert(std::make_pair(in_type, in_state));
		return true;
	}
	return false;
}

bool input_receiver::remove_key(event_type in_type, char in_state) {
	events_map::const_iterator it = m_received_events.find(in_type);
	if (it != m_received_events.end()) {
		if (it->second != in_state) {
			m_received_events.erase(it);
			return true;
		}
	}
	return false;
}
