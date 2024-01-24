#include "behavior.h"

#include "spaceship.h"
#include "globals.h"

void behavior::update(float delta_time, spaceship &in_object) {
	if (m_actions.empty())	return;

	handle_action(*m_cur_action, in_object);
}

void behavior::add_action(const action &in_action) {
	m_actions.push_front(in_action);
	if (m_actions.size() == 1) {
		m_cur_action = m_actions.begin();
	}
}

void behavior::handle_action(const action &in_action, spaceship &in_object) {
	switch (in_action.get_type()) {
	case action_type::AT_MOVE_FORWARD:
		in_object.move_forward();
		break;
	}
}
