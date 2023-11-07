#include "controller.h"
#include "input_receiver.h"

void controller::handle_input(input_receiver *in_receiver) {
	in_receiver->receive_key();
	for (auto it = in_receiver->m_commands.cbegin(); it != in_receiver->m_commands.cend(); ++it) {
		(*it)->execute(m_owner);
	}

}
