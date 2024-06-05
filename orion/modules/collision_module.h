#ifndef COLLISION_MODULE_H
#define COLLISION_MODULE_H

#include <vector>

#include "../interfaces/collidable.h"

class world_module;
class border;

class collision_module {
public:
	collision_module();
	~collision_module();

	void init_borders();

	void check_collision(world_module *world, collidable *object);
	bool intersect(const aabb &lhs, const aabb &rhs);

private:
	std::vector<border*> borders;
};
#endif // COLLISION_MODULE_H
