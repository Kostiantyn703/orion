#ifndef SPACESHIP_H
#define SPACESHIP_H

#include <memory>

#include "../input/controllable.h"
#include "../input/controller.h"

#include "../interfaces/movable.h"

#include "../gameplay/border.h"
#include "../gameplay/behavior.h"

#include "game_object.h"
#include "weapon.h"

class subscriber;

enum ship_type {
	ST_PLAYER = 0,
	ST_ENEMY = 1,
	ST_NONE
};

class spaceship : public game_object, public controllable {
public:
	spaceship(const vector2f &initial_point, const vector2f &forward_vector);
	virtual ~spaceship();

	virtual void init() override;

	void on_spawn(bool is_shooter);
	
	virtual bool on_intersect() override;

	virtual void update(float delta_time) override;

	virtual void move_forward() override;
	virtual void move_right() override;
	virtual void move_backward() override;
	virtual void move_left() override;
	virtual void shoot() override;

	virtual void reset_movement() override;


	virtual void borders_intersect(border_side side) override;

	void set_listener(subscriber *listener) { world = listener; }

	weapon *get_weapon() const { return gun; }
	behavior *get_behavior() const { return behavior_instance.get(); }

private:
	bool blocked_up		= false;
	bool blocked_right	= false;
	bool blocked_down	= false;
	bool blocked_left	= false;

	weapon *gun = nullptr;

	subscriber *world = nullptr;

	std::unique_ptr<behavior> behavior_instance;

	ship_type type;

	void init_weapon();
};

#endif // SPACESHIP_H
