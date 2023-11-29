#ifndef WORLD_MODULE_H
#define WORLD_MODULE_H

#include <vector>
#include <memory>

#include "game_object.h"
#include "controller.h"
#include "subscriber.h"
#include "collision_module.h"

#include "spaceship.h"
#include "bullet.h"
#include "meteor.h"

using object_storage = std::vector<game_object*>;

class world_module : public subscriber {
public:
	world_module();
	virtual ~world_module();

	void update(float delta_time);
	void remove_objects();
	
	void init_player(controller *in_controller);
	void init_objects();

	// TODO: create methods should go to spawner classes
	game_object *create_object(vector2f &in_position) const;

	spaceship *spawn_spaceship(vector2f &in_position, vector2f &in_forward_vector) const;
	bullet *spawn_bullet(const vector2f &in_position, const vector2f &in_forward_vector) const;
	meteor *spawn_meteor(const vector2f &in_position, const vector2f &in_forward_vector) const;

	virtual void on_notify(const vector2f &in_position, const vector2f &in_forward_vector) override;

	object_storage					m_objects;
private:
	std::unique_ptr<collision_module> m_colision_system;
};
#endif // WORLD_MODULE_H
