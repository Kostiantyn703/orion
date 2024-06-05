#include "input_receiver.h"
#include <SDL_log.h>
#include <algorithm>

void input_receiver::receive_key() {
	SDL_Event key_event;
	SDL_PollEvent(&key_event);
	enter_pressed = false;
	handle_key_down(key_event);
	handle_key_up(key_event);
}

void input_receiver::handle_key_down(const SDL_Event &key_event) {
	if (key_event.type & SDL_KEYDOWN) {
		switch (key_event.key.keysym.sym) {
		case SDLK_UP:
			add_command(new	move_forward_command(key_event.key.state, command_type::CT_UP));
			break;
		case SDLK_RIGHT:
			add_command(new move_right_command(key_event.key.state, command_type::CT_RIGHT));
			break;
		case SDLK_DOWN:
			add_command(new move_backward_command(key_event.key.state, command_type::CT_DOWN));
			break;
		case SDLK_LEFT:
			add_command(new move_left_command(key_event.key.state, command_type::CT_LEFT));
			break;
		case SDLK_SPACE:
			add_command(new shoot_command(key_event.key.state, command_type::CT_SHOOT));
			break;
		case SDLK_RETURN:
			if (enter_pressed) skip_return = true;
			break;
		}
	}
}

void input_receiver::handle_key_up(const SDL_Event &key_event) {
	if (key_event.type & SDL_KEYUP) {
		switch (key_event.key.keysym.sym) {
		case SDLK_UP:
			remove_command(command_type::CT_UP, key_event.key.state);
			break;
		case SDLK_RIGHT:
			remove_command(command_type::CT_RIGHT, key_event.key.state);
			break;
		case SDLK_DOWN:
			remove_command(command_type::CT_DOWN, key_event.key.state);
			break;
		case SDLK_LEFT:
			remove_command(command_type::CT_LEFT, key_event.key.state);
			break;
		case SDLK_SPACE:
			remove_command(command_type::CT_SHOOT, key_event.key.state);
			break;
		case SDLK_ESCAPE:
			esc_pressed = true;
			break;
		case SDLK_RETURN:
			if (!skip_return) enter_pressed = true;
			break;
		}
	}
}

bool input_receiver::add_command(command *input_command) {
	auto pred = [&input_command](command *cmnd) {
		return cmnd->get_type() == input_command->get_type();
	};
	commands_set::const_iterator it = find_if(commands.cbegin(), commands.end(), pred);
	if (it == commands.end()) {
		commands.insert(input_command);
		return true;
	}
	delete input_command;
	return false;
}

bool input_receiver::remove_command(command_type type, char state) {
	auto pred = [&type](command *cmnd) {
		return cmnd->get_type() == type;
	};
	commands_set::const_iterator it = find_if(commands.cbegin(), commands.end(), pred);
	if (it != commands.end()) {
		if ((*it)->get_state() != state) {
			delete *it;
			commands.erase(it);
			return true;
		}
	}
	return false;
}
