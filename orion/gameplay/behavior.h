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
	void set_type(condition_type type) { this->type = type; }
	condition_type get_type() const { return type; }

	void set_data(float data) { this->data = data; }
	float get_data() const { return data; }
private:
	condition_type type;
	float data;
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
	void set_type(action_type type) { this->type = type; }
	action_type get_type() const { return type; }

	void set_condition(const end_condition &condition) { this->condition = condition; }
	const end_condition& get_condition() const { return condition; }
private:
	action_type type;
	end_condition condition;
};

class behavior {
public:
	void init();

	void update(float delta_time, spaceship &ship);

	void add_action(const action &act);
	void handle_action(const action &act, spaceship &ship);
	bool handle_condition(const action &act, spaceship &ship);

	void action_change();
	void change_rotation(float rotation, spaceship &ship);
private:
	bool rotation_changed	= false;

	std::list<action> actions;
	std::list<action>::iterator action_it;
};
#endif // BEHAVIOR_H
