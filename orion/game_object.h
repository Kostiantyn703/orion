#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "globals.h"

class game_object {
public:
	game_object		(point &initial_point);
	game_object		(float initial_x, float initial_y);
	~game_object	();

	void update		(float delta_time);

	void set_position	(float in_x, float in_y);
	const point &get_position	() const {	return m_position;	}

private:
	float m_velocity = 200.f;
	point m_position;

};

#endif // GAME_OBJECT_H