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
#include "meteor_spawner.h"
#include "ship_spawner.h"

using object_storage = std::vector<game_object*>;

class world_module : public subscriber {
public:
	world_module();
	virtual ~world_module();

	void init();

	void update(float delta_time);
	void remove_objects();
	
	void init_player(controller *in_controller);

	bullet *spawn_bullet(const vector2f &in_position, const vector2f &in_forward_vector) const;

	virtual void on_notify(const vector2f &in_position, const vector2f &in_forward_vector) override;
	virtual void on_notify(game_object &in_object) override;

	object_storage					m_objects;

	std::vector<float> m_script_data;

	bool m_script_playing = false;

private:

	std::unique_ptr<collision_module> m_colision_system;

	std::unique_ptr<meteor_spawner> m_meteor_spawner;
	std::unique_ptr<ship_spawner>	m_ship_spawner;
};
#endif // WORLD_MODULE_H
