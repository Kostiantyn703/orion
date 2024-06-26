#include "collision_module.h"

#include "world_module.h"

collision_module::collision_module() {
	init_borders();
}

void collision_module::init_borders() {
	float offset = 20.f;

	vector2f upper_left(0.f, 0.f);
	vector2f down_left(0.f, WINDOW_HEIGHT - offset);
	vector2f upper_right(WINDOW_WIDTH - offset, 0.f);

	vector2f north_side(WINDOW_WIDTH, offset + 100.f);
	vector2f east_side(WINDOW_WIDTH, WINDOW_HEIGHT);
	vector2f south_side(WINDOW_WIDTH, WINDOW_HEIGHT);
	vector2f west_side(offset, WINDOW_HEIGHT);

	border *north = new border();
	aabb north_box(upper_left, north_side);
	north->set_aabb(north_box);
	north->set_side(border_side::BS_NORTH);
	north->set_mask(MASK_BORDER);

	border *east = new border();
	aabb east_box(upper_right, east_side);
	east->set_aabb(east_box);
	east->set_side(border_side::BS_EAST);
	east->set_mask(MASK_BORDER);

	border *south = new border();
	aabb south_box(down_left, south_side);
	south->set_aabb(south_box);
	south->set_side(border_side::BS_SOUTH);
	south->set_mask(MASK_BORDER);

	border *west = new border();
	aabb west_box(upper_left, west_side);
	west->set_aabb(west_box);
	west->set_side(border_side::BS_WEST);
	west->set_mask(MASK_BORDER);

	borders.push_back(north);
	borders.push_back(east);
	borders.push_back(south);
	borders.push_back(west);
}

collision_module::~collision_module() {
	for (std::vector<border*>::iterator it = borders.begin(); it != borders.end(); ++it) {
		delete *it;
	}
}

void collision_module::check_collision(world_module *world, collidable *object) {
	if (!object)
		return;

	if (object->get_mask() & MASK_PLAYER) {
		for (std::vector<border*>::const_iterator it = borders.cbegin(); it != borders.cend(); ++it) {
			if (intersect(object->get_aabb(), (*it)->get_aabb())) {
				object->borders_intersect((*it)->get_side());
			}
		}
	}

	for (object_storage::const_iterator it = world->objects.cbegin(); it != world->objects.cend(); ++it) {
		if (object == *it)	
			continue;

		if (object->get_mask() & (*it)->get_mask())	
			continue;

		if (intersect(object->get_aabb(), (*it)->get_aabb())) {
			bool player_killed = (*it)->on_intersect();
			world->set_game_over(player_killed);
			world->add_score((*it)->get_score_value());
			object->on_intersect();
		}
	}
}

bool collision_module::intersect(const aabb &lhs, const aabb &rhs) {
	bool x_check_min = lhs.get_origin().get_x() <= (rhs.get_origin().get_x() + rhs.get_size().get_x());
	bool x_check_max = (lhs.get_origin().get_x() + lhs.get_size().get_x()) >= rhs.get_origin().get_x();

	bool y_check_min = lhs.get_origin().get_y() <= (rhs.get_origin().get_y() + rhs.get_size().get_y());
	bool y_check_max = (lhs.get_origin().get_y() + lhs.get_size().get_y()) >= rhs.get_origin().get_y();

	bool result = x_check_min && x_check_max && y_check_min && y_check_max;

	return result;
}
