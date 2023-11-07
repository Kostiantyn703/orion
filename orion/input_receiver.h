#ifndef INPUT_RECEIVER_H
#define INPUT_RECEIVER_H

#include <unordered_set>
#include <SDL_events.h>
#include "controller.h"
#include "commands.h"

class input_receiver {
	using commands_set = std::unordered_set<command*>;
public:
	input_receiver()	{}
	~input_receiver()	{}

	void receive_key();
	void handle_key_down(const SDL_Event &in_event);
	void handle_key_up(const SDL_Event &in_event);

	bool add_command(command *in_command);
	bool remove_command(command_type in_type, char in_state);

private:
	commands_set m_received_commands;
};

#endif // INPUT_RECEIVER_H
