#include "bullet.h"

bullet::bullet(const vector2f &initial_point, const vector2f &in_forward_vector) 
	: game_object(initial_point)
{
	set_forward_vector(in_forward_vector);
	set_move_dir(in_forward_vector);
	set_velocity(BULLET_VELOCITY);
}

void bullet::update(float delta_time) {
	vector2f delta_vec = get_move_dir() * get_velocity() * delta_time ;
	set_origin(get_origin() + delta_vec);
	m_aabb.calculate(get_origin(), get_size(), SIZE_SCALAR);
	// TODO: temporary
	if (get_origin().get_y() < 0.f) {
		set_to_remove(true);
	}
}