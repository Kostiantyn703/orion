#ifndef WORLD_MODULE_H
#define WORLD_MODULE_H

#include <vector>

#include "game_object.h"
#include "controller.h"

class world_module {
	using object_storage = std::vector<game_object*>;
public:
	world_module();
	~world_module();

	void update(float delta_time);
	
	void init_player(controller *in_controller);
	void init_objects();

	game_object	*create_object(float in_x, float in_y) const;
	game_object *create_object(const point &in_position) const;

	object_storage					m_objects;
};
#endif // WORLD_MODULE_H
