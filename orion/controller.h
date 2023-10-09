#ifndef CONTROLLER_H
#define CONTROLLER_H

class controller {
public:
	controller();
	~controller();

	void handle_input(bool &out_active);
};
#endif // CONTROLLER_H