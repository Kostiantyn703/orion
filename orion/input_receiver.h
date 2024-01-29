#ifndef INPUT_RECEIVER_H
#define INPUT_RECEIVER_H

#include <unordered_set>
#include <SDL_events.h>

#include "commands.h"

class input_receiver {
	using commands_set = std::unordered_set<command*>;
public:
	input_receiver()	{}
	~input_receiver()	{}

	commands_set m_commands;

	void receive_key();

	bool esc_pressed = false;

private:
	void handle_key_down(const SDL_Event &in_event);
	void handle_key_up(const SDL_Event &in_event);

	bool add_command(command *in_command);
	bool remove_command(command_type in_type, char in_state);

};
#endif // INPUT_RECEIVER_H
