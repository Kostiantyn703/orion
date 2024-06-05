#include "behavior.h"

#include "../objects/spaceship.h"
#include "../utils/globals.h"

void behavior::init() {
	action_it = actions.begin();
}

void behavior::update(float delta_time, spaceship &ship) {
	if (actions.empty())
		return;

	if (action_it != actions.cend()) {
		handle_action(*action_it, ship);
		if (handle_condition(*action_it, ship))
			action_change();
	}

	if (!ship.get_weapon())
		return;
	
	if (ship.get_weapon()->get_can_shoot())
		ship.shoot();
}

void behavior::add_action(const action &act) {
	actions.push_back(act);
}

void behavior::handle_action(const action &act, spaceship &ship) {
	switch (act.get_type()) {
	case action_type::AT_MOVE_FORWARD:
		ship.move_forward();
		change_rotation(ZERO_ANGLE, ship);
		break;
	case action_type::AT_MOVE_LEFT:
		ship.move_left();
		change_rotation(REFLEX_ANGLE, ship);
		break;
	case action_type::AT_MOVE_RIGHT:
		ship.move_right();
		change_rotation(RIGHT_ANGLE, ship);
		break;
	case action_type::AT_MOVE_BACKWARD:
		ship.move_backward();
		change_rotation(STRAIGHT_ANGLE, ship);
		break;
	}
}

bool behavior::handle_condition(const action &act, spaceship &ship) {
	bool result = false;
	const end_condition &cond = act.get_condition();
	switch (cond.get_type()) {
	case condition_type::CT_POSITION_X:
		if (act.get_type() == action_type::AT_MOVE_LEFT) {
			if ((ship.get_center().get_x() - cond.get_data()) > FLOAT_PRECSISSION)
				result = true;
		}
		if (act.get_type() == action_type::AT_MOVE_RIGHT) {
			if ((ship.get_center().get_x() - cond.get_data()) < FLOAT_PRECSISSION)
				result = true;
		}
		break;
	case condition_type::CT_POSITION_Y:
		if (act.get_type() == action_type::AT_MOVE_FORWARD) {
			if ((ship.get_center().get_y() - cond.get_data()) > FLOAT_PRECSISSION)
				result = true;
		}
		if (act.get_type() == action_type::AT_MOVE_BACKWARD) {
			if ((ship.get_center().get_y() - cond.get_data()) < FLOAT_PRECSISSION)
				result = true;
		}
		break;
	}
	return result;
}

void behavior::action_change() {
	++action_it;
	rotation_changed = false;
}

void behavior::change_rotation(float rotation, spaceship &ship) {
	if (!rotation_changed) {
		ship.set_rotation(rotation);
		rotation_changed = true;
	}
}
