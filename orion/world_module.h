#ifndef WORLD_MODULE_H
#define WORLD_MODULE_H

#include <vector>

#include "game_object.h"
#include "controller.h"
#include "resource_module.h"

class texture;

class world_module {
	using object_storage = std::vector<game_object*>;
public:
	world_module();
	~world_module();

	void update(float delta_time);
	
	void init_player(controller *in_controller, const resource_module &in_resources);
	void init_objects(const resource_module &in_resources);

	void create_object(float in_x, float in_y, texture *in_texture);
	void create_object(object_type in_type, point &in_position, texture *in_texture);

	object_storage					m_objects;
};
#endif // WORLD_MODULE_H
