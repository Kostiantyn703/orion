#ifndef BEHAVIOR_H
#define BEHAVIOR_H

#include <list>
#include "globals.h"

class spaceship;

enum class condition_type {
	CT_POSITION,		// if condition means fly until position on the screen
	CT_NONE
};

class end_condition {
public:
	void set_type(condition_type in_type) { m_type = in_type; }
	condition_type get_type() const { return m_type; }

	void set_data(float in_x, float in_y) { m_data = vector2f(in_x, in_y); }
private:
	condition_type m_type;
	vector2f m_data;
};

enum class action_type {
	AT_MOVE_FORWARD,
	AT_MOVE_LEFT,
	AT_MOVE_RIGHT,
	AT_NONE
};


class action {
public:
	void set_type(action_type in_type) { m_type = in_type; }
	action_type get_type() const { return m_type; }

private:
	action_type m_type;
	end_condition m_condition;
};

class behavior {
public:
	behavior() {}
	~behavior() {}

	void update(float delta_time, spaceship &in_object);

	void add_action(const action &in_action);

	void handle_action(const action &in_action, spaceship &in_object);

private:
	std::list<action> m_actions;
	
	std::list<action>::const_iterator m_cur_action;
};

#endif // BEHAVIOR_H

