#ifndef COLLISION_MODULE_H
#define COLLISION_MODULE_H

#include <vector>

#include "../interfaces/collidable.h"
#include "../utils/globals.h"

class world_module;
class border;

class collision_module {
public:
	collision_module();
	~collision_module();

	void init_borders();

	void check_collision(world_module *in_world, collidable *in_object);
	bool intersect(const aabb &lhs, const aabb &rhs);

private:
	std::vector<border*> m_borders;
};
#endif // COLLISION_MODULE_H
