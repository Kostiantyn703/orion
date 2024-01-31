#include "bullet.h"

bullet::bullet(const vector2f &initial_point, const vector2f &in_forward_vector) 
	: game_object(initial_point)
{
	set_forward_vector(in_forward_vector);
	set_move_dir(in_forward_vector);
	set_velocity(BULLET_VELOCITY);
}

void bullet::update(float delta_time) {
	game_object::update(delta_time);
	if (get_origin().get_y() < 0.f || get_origin().get_y() > WINDOW_HEIGHT) {
		set_to_remove(true);
	}
}