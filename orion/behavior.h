#ifndef BEHAVIOR_H
#define BEHAVIOR_H

class spaceship;

class behavior {
public:
	behavior() {}
	~behavior() {}

	void update(float delta_time, spaceship &in_object);

	bool changed = false;
};

#endif // BEHAVIOR_H

