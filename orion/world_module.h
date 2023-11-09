#ifndef WORLD_MODULE_H
#define WORLD_MODULE_H

#include <vector>

#include "game_object.h"
#include "controller.h"
#include "subscriber.h"

class world_module : public subscriber {
	using object_storage = std::vector<game_object*>;
public:
	world_module() {}
	virtual ~world_module();

	void update(float delta_time);
	
	void init_player(controller *in_controller);
	void init_objects();

	game_object	*create_object(float in_x, float in_y) const;
	game_object *create_object(const point &in_position) const;

	virtual void on_notify(game_object *in_object) override;

	object_storage					m_objects;
private:
	void spawn_bullet(const point &in_position);
};
#endif // WORLD_MODULE_H
