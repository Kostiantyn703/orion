#ifndef MOVABLE_H
#define MOVABLE_H

#include "../utils/globals.h"

class movable {
protected:
	movable() : velocity(0.f), direction_vector(0.f, 0.f), forward_vector(0.f, 0.f) {}
	virtual ~movable() {}

	void set_direction(vector2f direction) { direction_vector = direction; }
	vector2f get_direction() const { return direction_vector; }
	
	void set_forward_vector(vector2f forward_vector) { this->forward_vector = forward_vector; }
	vector2f get_forward_vector() const { return forward_vector; }

	void set_velocity(float velocity) { this->velocity = velocity; }
	float get_velocity() const { return velocity; }

	void merge_movement(vector2f &direction) { direction_vector = direction_vector + direction; }
private:
	float velocity;
	vector2f direction_vector;
	vector2f forward_vector;
};
#endif // MOVABLE_H
