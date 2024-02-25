#ifndef COMMANDS_H
#define COMMANDS_H

#include <SDL_log.h>
#include "controllable.h"

enum class command_type {
	CT_UP,
	CT_RIGHT,
	CT_DOWN,
	CT_LEFT,
	CT_SHOOT,
	CT_NONE
};

class command {
public:
	command(char in_state, command_type in_type) : m_state(in_state), m_type(in_type) {}
	virtual ~command() {}

	virtual void execute(controllable *in_controllable) = 0;

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

	void execute(controllable *in_controllable) override {
		in_controllable->move_forward();
	}
};

class move_right_command : public command {
public:
	move_right_command(char in_state, command_type in_type) : command(in_state, in_type) {}
	virtual ~move_right_command() {}

	void execute(controllable *in_controllable) override {
		in_controllable->move_right();
	}
};

class move_backward_command : public command {
public:
	move_backward_command(char in_state, command_type in_type) : command(in_state, in_type) {}
	virtual ~move_backward_command() {}

	void execute(controllable *in_controllable) override {
		in_controllable->move_backward();
	}
};

class move_left_command : public command {
public:
	move_left_command(char in_state, command_type in_type) : command(in_state, in_type) {}
	virtual ~move_left_command() {}

	void execute(controllable *in_controllable) override {
		in_controllable->move_left();
	}
};

class shoot_command : public command {
public:
	shoot_command(char in_state, command_type in_type) : command(in_state, in_type) {}
	virtual ~shoot_command() {}

	void execute(controllable *in_controllable) override {
		in_controllable->shoot();
	}
};
#endif // COMMANDS_H
