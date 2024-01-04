#ifndef COLLISION_MODULE_H
#define COLLISION_MODULE_H

#include "collidable.h"
#include "globals.h"

class world_module;

class collision_module {
public:
	collision_module()	{}
	~collision_module()	{}

	void check_collision(const world_module *in_world, collidable *in_object);
	bool intersect(const aabb &lhs, const aabb &rhs);
};

#endif // COLLISION_MODULE_H
