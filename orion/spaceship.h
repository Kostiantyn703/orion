#ifndef SPACESHIP_H
#define SPACESHIP_H

#include "controllable.h"
#include "game_object.h"
#include "movable.h"
#include "weapon.h"

class subscriber;

class spaceship : public game_object, public controllable, public movable {
public:
	spaceship(const vector2f &initial_point, const vector2f &in_forward_vector);
	spaceship(const vector2f &initial_point, const vector2f &in_forward_vector, float in_velocity);

	virtual ~spaceship();

	virtual void init() override;

	virtual void update(float delta_time) override;
	// ~ controllable interface
	virtual void move_forward() override;
	virtual void move_right() override;
	virtual void move_backward() override;
	virtual void move_left() override;
	virtual void shoot() override;
	// ~ end controllable interface

	void set_listener(subscriber *in_listener) { m_listener = in_listener; }

private:
	weapon *m_weapon = nullptr;
	// for now it's world
	subscriber *m_listener = nullptr;
};

#endif // SPACESHIP_H
