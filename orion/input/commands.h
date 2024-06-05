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
	command(char state, command_type type) {
		this->state = state;
		this->type = type;
	}

	virtual ~command() {}

	virtual void execute(controllable *object) = 0;

	char get_state() const { return state; }
	command_type get_type() const { return type; }
private:
	char state;
	command_type type;
};

class move_forward_command : public command {
public:
	move_forward_command(char state, command_type type) : command(state, type) {}
	virtual ~move_forward_command() {}

	void execute(controllable *object) override {
		object->move_forward();
	}
};

class move_right_command : public command {
public:
	move_right_command(char state, command_type type) : command(state, type) {}
	virtual ~move_right_command() {}

	void execute(controllable *object) override {
		object->move_right();
	}
};

class move_backward_command : public command {
public:
	move_backward_command(char state, command_type type) : command(state, type) {}
	virtual ~move_backward_command() {}

	void execute(controllable *object) override {
		object->move_backward();
	}
};

class move_left_command : public command {
public:
	move_left_command(char state, command_type type) : command(state, type) {}
	virtual ~move_left_command() {}

	void execute(controllable *object) override {
		object->move_left();
	}
};

class shoot_command : public command {
public:
	shoot_command(char state, command_type type) : command(state, type) {}
	virtual ~shoot_command() {}

	void execute(controllable *object) override {
		object->shoot();
	}
};
#endif // COMMANDS_H
