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

	void update(float delta_time);

	void set_owner(controllable *in_controllable) { m_owner = in_controllable; }
	const controllable *get_owner() const { return m_owner; }
	//void add_object(controllable &in_object);
private:
	//std::vector<controllable*> m_enemies;
	controllable *m_owner = nullptr;
	bool is_moving = false;
	bool changed = false;
	float change_timer = 15.f;
};
#endif // CONTROLLER_H
