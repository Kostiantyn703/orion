#ifndef CONTROLLER_H
#define CONTROLLER_H

class application;

class controller {
public:
	controller();
	~controller();

	void handle_input(application &in_app);
};
#endif // CONTROLLER_H