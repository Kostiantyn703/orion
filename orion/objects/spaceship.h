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
	spaceship(const vector2f &initial_point, const vector2f &in_forward_vector);
	spaceship(const vector2f &initial_point, const vector2f &in_forward_vector, float in_velocity);

	virtual ~spaceship();

	virtual void init() override;

	virtual void on_spawn(bool is_shooter) override;
	virtual bool on_intersect() override;

	virtual void update(float delta_time) override;
	// ~ controllable interface
	virtual void move_forward() override;
	virtual void move_right() override;
	virtual void move_backward() override;
	virtual void move_left() override;
	virtual void shoot() override;

	virtual void reset_movement() override;
	// ~ end controllable interface

	virtual void borders_intersect(border_side in_side) override;

	void set_listener(subscriber *in_listener) { m_listener = in_listener; }

	weapon		*get_weapon()	const	{	return m_weapon;			}
	behavior	*get_behavior()	const	{	return m_behavior.get();	}

private:
	bool blocked_up		= false;
	bool blocked_right	= false;
	bool blocked_down	= false;
	bool blocked_left	= false;

	weapon *m_weapon = nullptr;
	// for now it's world
	subscriber *m_listener = nullptr;

	std::unique_ptr<behavior> m_behavior;

	ship_type m_type;

	void init_weapon();
};

#endif // SPACESHIP_H
