#include "controller.h"

#include "input_receiver.h"

#include "../utils/globals.h"

void controller::handle_input(input_receiver *in_receiver) {
	in_receiver->receive_key();
	if (!m_owner) return;
	for (auto it = in_receiver->m_commands.cbegin(); it != in_receiver->m_commands.cend(); ++it) {
		(*it)->execute(m_owner);
	}
}
