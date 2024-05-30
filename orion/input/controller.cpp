#include "controller.h"

#include "input_receiver.h"

void input_controller::handle_input(input_receiver *receiver) {
	receiver->receive_key();

	if (!owner)
		return;

	for (std::unordered_set<command*>::iterator it = receiver->m_commands.cbegin(); it != receiver->m_commands.cend(); ++it)
		(*it)->execute(owner);
}
