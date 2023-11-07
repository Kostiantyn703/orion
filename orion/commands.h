#ifndef COMMANDS_H
#define COMMANDS_H

class command {
public:
	virtual command(char in_state) : m_state(in_state) {}
	virtual ~command() {}

	void execute() = 0;

	char m_state = 0;
};

class move_forward_command : public command {
public:
	virtual move_forward_command(char in_state) : command(in_state) {}
	virtual ~move_forward_command() {}

	void execute() {
		SDL_Log("Execute move FORWARD.");
	}
};

class move_right_command : public command {
public:
	virtual move_right_command(char in_state) : command(in_state) {}
	virtual ~move_right_command() {}

	void execute() {
		SDL_Log("Execute move RIGHT.");
	}
};
#endif // COMMANDS_H
