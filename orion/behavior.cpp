#include "behavior.h"

#include "spaceship.h"
#include "globals.h"

void behavior::update(float delta_time, spaceship &in_object) {
	in_object.move_forward();
	if (!changed && in_object.get_origin().get_y() > WINDOW_HEIGHT * 0.5f) {
		in_object.reset_movement();
		vector2f dir(-1.f, 0.f);
		in_object.change_direction(dir);
		changed = true;
	}
}
