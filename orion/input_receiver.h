#ifndef INPUT_RECEIVER_H
#define INPUT_RECEIVER_H

#include <unordered_map>
#include <SDL_events.h>
#include "controller.h"

enum class event_type {
	ET_UP,
	ET_RIGHT,
	ET_DOWN,
	ET_LEFT,
	ET_NONE
};

class input_receiver {
	using events_map = std::unordered_map<event_type, char>;
public:
	input_receiver()	{}
	~input_receiver()	{}

	void receive_key();
	void handle_key_down(const SDL_Event &in_event);
	void handle_key_up(const SDL_Event &in_event);
	
	bool add_key(event_type in_type, char in_state);
	bool remove_key(event_type in_type, char in_state);

private:
	events_map m_received_events;
};

#endif // INPUT_RECEIVER_H
