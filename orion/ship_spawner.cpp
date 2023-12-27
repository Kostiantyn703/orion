#include "ship_spawner.h"

#include "spaceship.h"

void ship_spawner::notify() {


}

game_object *ship_spawner::spawn_object(const vector2f &in_position, const vector2f &in_forward_vector) const {
	return new spaceship(in_position, in_forward_vector);
}

spaceship *ship_spawner::spawn_spaceship(const vector2f &in_position, const vector2f &in_forward_vector) const {
	return new spaceship(in_position, in_forward_vector);
}