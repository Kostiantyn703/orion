#ifndef BEHAVIOR_H
#define BEHAVIOR_H

#include <list>
#include <map>
#include <string>

#include "../utils/globals.h"

class spaceship;

enum class condition_type {
	CT_POSITION_X,
	CT_POSITION_Y,
	CT_NONE
};

class end_condition {
public:
	void set_type(condition_type in_type) { m_type = in_type; }
	condition_type get_type() const { return m_type; }

	void set_data(float in_data) { m_data = in_data; }
	float get_data() const { return m_data; }
private:
	condition_type m_type;
	float m_data;
};

enum class action_type {
	AT_MOVE_FORWARD,
	AT_MOVE_BACKWARD,
	AT_MOVE_LEFT,
	AT_MOVE_RIGHT,
	AT_NONE
};

extern std::map<std::string, action_type> actions_map;
extern std::map<std::string, condition_type> conditions_map;

class action {
public:
	void set_type(action_type in_type) { m_type = in_type; }
	action_type get_type() const { return m_type; }

	void set_condition(const end_condition &in_cond) { m_condition = in_cond; }
	const end_condition& get_condition() const { return m_condition; }
private:
	action_type m_type;
	end_condition m_condition;
};

class behavior {
public:
	behavior() {}
	~behavior() {}

	void init();

	void update				(float delta_time, spaceship &in_object);

	void add_action			(const action &in_action);
	void handle_action		(const action &in_action, spaceship &in_object);
	bool handle_condition	(const action &in_action, spaceship &in_object);

	void on_action_change	();
	void change_rotation	(float in_rot, spaceship &in_object);
private:
	bool rotation_changed	= false;

	std::list<action> m_actions;
	std::list<action>::iterator m_cur_action;
};

#endif // BEHAVIOR_H

