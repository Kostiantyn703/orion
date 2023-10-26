#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "globals.h"
#include "renderable.h"

enum class direction {
	D_UP,
	D_RIGHT,
	D_DOWN,
	D_LEFT,
	D_NONE
};

class game_object : public renderable {
public:
	game_object		(point &initial_point);
	game_object		(float initial_x, float initial_y);

	game_object		(game_object &in_obj);

	virtual ~game_object() {}

	void update		(float delta_time);

	virtual void draw(const shader_program &in_shader) override;

	void set_position	(float in_x, float in_y);
	const point &get_position	() const {	return m_position;	}

	void set_direction(direction in_direction) { m_direction = in_direction; }
	point get_direction() const;

private:
	float m_velocity = 1000.f;
	point m_position;
	direction m_direction;
};

#endif // GAME_OBJECT_H