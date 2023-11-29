#include "meteor.h"

meteor::meteor(const vector2f &initial_point, const vector2f &in_forward_vector)
	: game_object(initial_point)
{
	set_forward_vector(in_forward_vector);
	set_move_dir(in_forward_vector);
}

void meteor::update(float delta_time) {
	vector2f delta_vec = get_move_dir() * delta_time;
	set_origin(get_origin() + delta_vec);
	m_aabb.calculate(get_origin(), get_size());
}
