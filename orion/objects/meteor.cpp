#include "meteor.h"

meteor::meteor(const vector2f &initial_point, const vector2f &forward_vector, const float velocity)
	: game_object(initial_point)
{
	set_forward_vector	(forward_vector);
	set_move_dir		(forward_vector);
	set_velocity		(velocity);
	set_score_value		(METEOR_SCORE);
}

void meteor::init() {
	calculate_origin();
}

void meteor::update(float delta_time) {
	game_object::update(delta_time);

	float cur_rot = get_rotation();
	cur_rot += delta_time * METEOR_ROTATION_VELOCITY;
	set_rotation(cur_rot);

	if (get_origin().get_y() > WINDOW_HEIGHT + OUT_OFFSET)
		set_to_remove(true);
}
