#include "input_receiver.h"
#include <SDL_log.h>
#include <algorithm>

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
			if (add_command(new	move_forward_command(in_event.key.state, command_type::ET_UP))) {
				SDL_Log("[UP]");
			}
			break;
		case SDLK_RIGHT:
			if (add_command(new move_right_command(in_event.key.state, command_type::ET_RIGHT))) {
				SDL_Log("[RIGHT]");
			}
			break;
		case SDLK_DOWN:
			/*if (add_command(command_type::ET_DOWN, in_event.key.state)) {
				SDL_Log("[DOWN]");
			}*/
			break;
		case SDLK_LEFT:
			/*if (add_command(command_type::ET_LEFT, in_event.key.state)) {
				SDL_Log("[LEFT]");
			}*/
			break;
		}
	}
}

void input_receiver::handle_key_up(const SDL_Event &in_event) {
	if (in_event.type & SDL_KEYUP) {
		switch (in_event.key.keysym.sym) {
		case SDLK_UP:
			if (remove_command(command_type::ET_UP, in_event.key.state)) {
				SDL_Log("[UP] released");
			}
			break;
		case SDLK_RIGHT:
			if (remove_command(command_type::ET_RIGHT, in_event.key.state)) {
				SDL_Log("[RIGHT] released");
			}
			break;
		case SDLK_DOWN:
			if (remove_command(command_type::ET_DOWN, in_event.key.state)) {
				SDL_Log("[DOWN] released");
			}
			break;
		case SDLK_LEFT:
			if (remove_command(command_type::ET_LEFT, in_event.key.state)) {
				SDL_Log("[LEFT] released");
			}
			break;
		}
	}
}

bool input_receiver::add_command(command *in_command) {
	auto pred = [&in_command](command *curr_command) {
		return curr_command->get_type() == in_command->get_type();
	};
	commands_set::const_iterator it = find_if(m_received_commands.cbegin(), m_received_commands.end(), pred);
	if (it == m_received_commands.end()) {
		m_received_commands.insert(in_command);
		return true;
	}
	delete in_command;
	return false;
}

bool input_receiver::remove_command(command_type in_type, char in_state) {
	auto pred = [&in_type](command *curr_command) {
		return curr_command->get_type() == in_type;
	};
	commands_set::const_iterator it = find_if(m_received_commands.cbegin(), m_received_commands.end(), pred);
	if (it != m_received_commands.end()) {
		if ((*it)->get_state() != in_state) {
			delete *it;
			m_received_commands.erase(it);
			return true;
		}
	}
	return false;
}
