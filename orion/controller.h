#ifndef CONTROLLER_H
#define CONTROLLER_H

class input_receiver;
class controllable;

class controller {
public:
	controller() {}
	~controller() {}

	void set_owner(controllable *in_controllable) { m_owner = in_controllable; }

	void handle_input(input_receiver *in_receiver);
private:
	controllable *m_owner = nullptr;
};
#endif // CONTROLLER_H
