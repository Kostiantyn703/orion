#ifndef CONTROLLER_H
#define CONTROLLER_H

class input_receiver;
class controllable;

class input_controller {
public:
	void set_owner(controllable *owner) { this->owner = owner; }
	void handle_input(input_receiver *receiver);

private:
	controllable *owner = nullptr;
};
#endif // CONTROLLER_H
