#ifndef INPUT_RECEIVER_H
#define INPUT_RECEIVER_H
#include <string>
#include <vector>

class input_receiver {
public:
	input_receiver();
	~input_receiver();

	void receive_key();
private:
	std::vector<std::string> m_recieved_keys;
};

#endif // INPUT_RECEIVER_H
