#include "collision_module.h"

#include "world_module.h"

void collision_module::check_collision(const world_module *in_world, collidable *in_object) {
	for (object_storage::const_iterator it = in_world->m_objects.cbegin(); it != in_world->m_objects.cend(); ++it) {
		if (in_object == *it)	continue;
		if (in_object->get_mask() & (*it)->get_mask())	continue;

		if (intersect(in_object->get_aabb(), (*it)->get_aabb())) {
			(*it)->on_intersect();
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
