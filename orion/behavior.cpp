#include "behavior.h"

#include "spaceship.h"
#include "globals.h"

void behavior::init() {
	m_cur_action = m_actions.begin();
}

void behavior::update(float delta_time, spaceship &in_object) {
	if (m_actions.empty())	return;

	if (m_cur_action != m_actions.cend()) {
		handle_action(*m_cur_action, in_object);
		if (handle_condition(*m_cur_action, in_object)) {
			++m_cur_action;
		}
	}
}

void behavior::add_action(const action &in_action) {
	m_actions.push_back(in_action);
}

void behavior::handle_action(const action &in_action, spaceship &in_object) {
	switch (in_action.get_type()) {
	case action_type::AT_MOVE_FORWARD:
		in_object.move_forward();
		break;
	case action_type::AT_MOVE_LEFT:
		in_object.move_left();
		break;
	case action_type::AT_MOVE_RIGHT:
		in_object.move_right();
		break;
	}
}

bool behavior::handle_condition(const action &in_action, spaceship &in_object) {
	bool result = false;
	const end_condition &cond = in_action.get_condition();
	switch (cond.get_type()) {
	case condition_type::CT_POSITION_X:
		if ((in_object.get_origin().get_x() - cond.get_data()) > 0.001) {
			result = true;
		}
		break;
	case condition_type::CT_POSITION_Y:
		if ((in_object.get_origin().get_y() - cond.get_data()) > 0.001) {
			result = true;
		}
		break;
	}
	return result;
}
