#include "controller.h"
#include "input_receiver.h"

void controller::handle_input(input_receiver *in_receiver) {
	in_receiver->receive_key();
	for (auto it = in_receiver->m_commands.cbegin(); it != in_receiver->m_commands.cend(); ++it) {
		(*it)->execute(m_owner);
	}
}

void enemy_controller::update(float delta_time) {
	if (!is_moving && m_owner) {
		m_owner->move_forward();
		is_moving = true;
	}
	change_timer -= delta_time;
	if (!changed && change_timer < 0.f) {
		m_owner->reset_movement();
		changed = true;
		m_owner->move_right();
	}
}
