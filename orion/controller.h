#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <vector>

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

class enemy_controller {
public:
	enemy_controller() {}
	~enemy_controller() {}

	void set_owner(controllable *in_controllable) { m_owner = in_controllable; }
	//void add_object(controllable &in_object);
private:
	//std::vector<controllable*> m_enemies;
	controllable *m_owner = nullptr;

};
#endif // CONTROLLER_H
