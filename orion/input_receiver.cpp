#include "input_receiver.h"
#include <SDL_log.h>
#include <algorithm>

void input_receiver::receive_key() {
	SDL_Event curr_event;
	SDL_PollEvent(&curr_event);
	enter_pressed = false;
	handle_key_down(curr_event);
	handle_key_up(curr_event);
}

void input_receiver::handle_key_down(const SDL_Event &in_event) {
	if (in_event.type & SDL_KEYDOWN) {
		switch (in_event.key.keysym.sym) {
		case SDLK_UP:
			add_command(new	move_forward_command(in_event.key.state, command_type::CT_UP));
			break;
		case SDLK_RIGHT:
			add_command(new move_right_command(in_event.key.state, command_type::CT_RIGHT));
			break;
		case SDLK_DOWN:
			add_command(new move_backward_command(in_event.key.state, command_type::CT_DOWN));
			break;
		case SDLK_LEFT:
			add_command(new move_left_command(in_event.key.state, command_type::CT_LEFT));
			break;
		case SDLK_SPACE:
			add_command(new shoot_command(in_event.key.state, command_type::CT_SHOOT));
			break;
		case SDLK_RETURN:
			if (enter_pressed) skip_return = true;
			break;
		}
	}
}

void input_receiver::handle_key_up(const SDL_Event &in_event) {
	if (in_event.type & SDL_KEYUP) {
		switch (in_event.key.keysym.sym) {
		case SDLK_UP:
			remove_command(command_type::CT_UP, in_event.key.state);
			break;
		case SDLK_RIGHT:
			remove_command(command_type::CT_RIGHT, in_event.key.state);
			break;
		case SDLK_DOWN:
			remove_command(command_type::CT_DOWN, in_event.key.state);
			break;
		case SDLK_LEFT:
			remove_command(command_type::CT_LEFT, in_event.key.state);
			break;
		case SDLK_SPACE:
			remove_command(command_type::CT_SHOOT, in_event.key.state);
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

bool input_receiver::add_command(command *in_command) {
	auto pred = [&in_command](command *curr_command) {
		return curr_command->get_type() == in_command->get_type();
	};
	commands_set::const_iterator it = find_if(m_commands.cbegin(), m_commands.end(), pred);
	if (it == m_commands.end()) {
		m_commands.insert(in_command);
		return true;
	}
	delete in_command;
	return false;
}

bool input_receiver::remove_command(command_type in_type, char in_state) {
	auto pred = [&in_type](command *curr_command) {
		return curr_command->get_type() == in_type;
	};
	commands_set::const_iterator it = find_if(m_commands.cbegin(), m_commands.end(), pred);
	if (it != m_commands.end()) {
		if ((*it)->get_state() != in_state) {
			delete *it;
			m_commands.erase(it);
			return true;
		}
	}
	return false;
}
