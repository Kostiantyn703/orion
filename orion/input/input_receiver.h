#ifndef INPUT_RECEIVER_H
#define INPUT_RECEIVER_H

#include <unordered_set>
#include <SDL_events.h>

#include "commands.h"

class input_receiver {
	using commands_set = std::unordered_set<command*>;
public:
	commands_set commands;

	void receive_key();

	bool esc_pressed = false;
	bool enter_pressed = false;
	bool skip_return = false;
	
private:
	void handle_key_down(const SDL_Event &key_event);
	void handle_key_up(const SDL_Event &key_event);

	bool add_command(command *input_command);
	bool remove_command(command_type type, char state);

};
#endif // INPUT_RECEIVER_H
