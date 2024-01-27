#ifndef SPACESHIP_H
#define SPACESHIP_H

#include "controllable.h"
#include "game_object.h"
#include "movable.h"
#include "weapon.h"
#include "controller.h"
#include "border.h"
#include "behavior.h"
#include <memory>

class subscriber;

class spaceship : public game_object, public controllable, public movable {
public:
	spaceship(const vector2f &initial_point, const vector2f &in_forward_vector);
	spaceship(const vector2f &initial_point, const vector2f &in_forward_vector, float in_velocity);

	virtual ~spaceship();

	virtual void init() override;
	// for enemies 
	virtual void on_spawn() override;

	virtual void update(float delta_time) override;
	// ~ controllable interface
	virtual void move_forward() override;
	virtual void move_right() override;
	virtual void move_backward() override;
	virtual void move_left() override;
	virtual void shoot() override;

	virtual void reset_movement() override;
	virtual void change_direction(const int in_dir) override;
	// ~ end controllable interface

	virtual void borders_intersect(border_side in_side) override;

	void set_listener(subscriber *in_listener) { m_listener = in_listener; }

	behavior *get_behavior() const { return m_behavior.get() ; }

private:
	bool blocked_up		= false;
	bool blocked_right	= false;
	bool blocked_down	= false;
	bool blocked_left	= false;

	weapon *m_weapon = nullptr;
	// for now it's world
	subscriber *m_listener = nullptr;

	std::unique_ptr<behavior> m_behavior;

	enum class ship_type {
		ST_PLAYER,
		ST_ENEMY,
		ST_NONE
	};

	ship_type m_type;
};

#endif // SPACESHIP_H
