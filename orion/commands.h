#ifndef COMMANDS_H
#define COMMANDS_H
#include <SDL_log.h>

enum class command_type {
	ET_UP,
	ET_RIGHT,
	ET_DOWN,
	ET_LEFT,
	ET_NONE
};

class command {
public:
	command(char in_state, command_type in_type) : m_state(in_state), m_type(in_type) {}
	virtual ~command() {}

	virtual void execute() = 0;

	char get_state() const { return m_state; }
	command_type get_type() const { return m_type; }
private:
	char m_state;
	command_type m_type;
};

class move_forward_command : public command {
public:
	move_forward_command(char in_state, command_type in_type) : command(in_state, in_type) {}
	virtual ~move_forward_command() {}

	void execute() override {
		SDL_Log("Execute move FORWARD.");
	}
};

class move_right_command : public command {
public:
	move_right_command(char in_state, command_type in_type) : command(in_state, in_type) {}
	virtual ~move_right_command() {}

	void execute() override {
		SDL_Log("Execute move RIGHT.");
	}
};
#endif // COMMANDS_H
