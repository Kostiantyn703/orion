#include "meteor.h"

meteor::meteor(const vector2f &initial_point, const vector2f &in_forward_vector, const float in_velocity)
	: game_object(initial_point)
{
	set_forward_vector	(in_forward_vector);
	set_move_dir		(in_forward_vector);
	set_velocity		(in_velocity);
	set_score_value		(METEOR_SCORE);
}

void meteor::init() {
	recalc_pos();
}

void meteor::update(float delta_time) {
	game_object::update(delta_time);
	float cur_rot = get_rotation();
	cur_rot += delta_time * 2;
	set_rotation(cur_rot);

	if (get_origin().get_y() > WINDOW_HEIGHT + OUT_OFFSET) {
		set_to_remove(true);
	}
}
