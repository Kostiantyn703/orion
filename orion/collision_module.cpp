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

	m_borders.push_back(north);
	m_borders.push_back(east);
	m_borders.push_back(south);
	m_borders.push_back(west);
}

collision_module::~collision_module() {
	for (auto it = m_borders.begin(); it != m_borders.end(); ++it) {
		delete *it;
	}
}

void collision_module::check_collision(world_module *in_world, collidable *in_object) {
	if (in_object->get_mask() & MASK_PLAYER) {
		for (std::vector<border*>::const_iterator local_it = m_borders.cbegin(); local_it != m_borders.cend(); ++local_it) {
			if (intersect(in_object->get_aabb(), (*local_it)->get_aabb())) {
				in_object->borders_intersect((*local_it)->get_side());
			}
		}
	}

	for (object_storage::const_iterator it = in_world->m_objects.cbegin(); it != in_world->m_objects.cend(); ++it) {
		if (in_object == *it)	continue;
		if (in_object->get_mask() & (*it)->get_mask())	continue;
		if (intersect(in_object->get_aabb(), (*it)->get_aabb())) {
			(*it)->on_intersect();
			in_world->add_score((*it)->get_score_value());
			// bullet should disappear
			in_object->on_intersect();
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
