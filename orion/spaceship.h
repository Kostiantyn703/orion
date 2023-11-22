#ifndef SPACESHIP_H
#define SPACESHIP_H

#include "controllable.h"
#include "game_object.h"
#include "weapon.h"

class spaceship : public game_object, public controllable {
public:
	spaceship(vector2f &initial_point);
	spaceship(float initial_x, float initial_y);

	virtual ~spaceship();

	virtual void update(float delta_time) override;
	// TODO: implement
	virtual void move_forward() override {}
	virtual void move_right() override {}
	virtual void move_backward() override {}
	virtual void move_left() override {}

	virtual void shoot() override;
private:

	weapon *m_weapon = nullptr;
};

#endif // SPACESHIP_H
