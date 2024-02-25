#include "behavior.h"

#include "../objects/spaceship.h"
#include "../utils/globals.h"

void behavior::init() {
	m_cur_action = m_actions.begin();
}

void behavior::update(float delta_time, spaceship &in_object) {
	if (m_actions.empty())	return;

	if (m_cur_action != m_actions.cend()) {
		handle_action(*m_cur_action, in_object);
		if (handle_condition(*m_cur_action, in_object)) {
			++m_cur_action;
			on_action_change();
		}
	}

	if (!in_object.get_weapon())	return;
	
	if (in_object.get_weapon()->can_shoot()) {
		in_object.shoot();
	}
}

void behavior::add_action(const action &in_action) {
	m_actions.push_back(in_action);
}

void behavior::handle_action(const action &in_action, spaceship &in_object) {
	switch (in_action.get_type()) {
	case action_type::AT_MOVE_FORWARD:
		in_object.move_forward();
		change_rotation(0.f, in_object);
		break;
	case action_type::AT_MOVE_LEFT:
		in_object.move_left();
		change_rotation(270.f, in_object);
		break;
	case action_type::AT_MOVE_RIGHT:
		in_object.move_right();
		change_rotation(90.f, in_object);
		break;
	case action_type::AT_MOVE_BACKWARDS:
		in_object.move_backward();
		change_rotation(180.f, in_object);
		break;
	}
}

bool behavior::handle_condition(const action &in_action, spaceship &in_object) {
	bool result = false;
	const end_condition &cond = in_action.get_condition();
	switch (cond.get_type()) {
	case condition_type::CT_POSITION_X:
		if (in_action.get_type() == action_type::AT_MOVE_LEFT) {
			if ((in_object.get_center().get_x() - cond.get_data()) > 0.001) {
				result = true;
			}
		}
		if (in_action.get_type() == action_type::AT_MOVE_RIGHT) {
			if ((in_object.get_center().get_x() - cond.get_data()) < 0.001) {
				result = true;
			}
		}
		break;
	case condition_type::CT_POSITION_Y:
		if (in_action.get_type() == action_type::AT_MOVE_FORWARD) {
			if ((in_object.get_center().get_y() - cond.get_data()) > 0.001) {
				result = true;
			}
		}
		if (in_action.get_type() == action_type::AT_MOVE_BACKWARDS) {
			if ((in_object.get_center().get_y() - cond.get_data()) < 0.001) {
				result = true;
			}
		}
		break;
	}
	return result;
}

void behavior::on_action_change() {
	rotation_changed = false;
}

void behavior::change_rotation(float in_rot, spaceship &in_object) {
	if (!rotation_changed) {
		in_object.set_rotation(in_rot);
		rotation_changed = true;
	}
}
