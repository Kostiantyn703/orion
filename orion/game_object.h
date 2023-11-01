#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "globals.h"
#include "renderable.h"
#include "movable.h"

enum class object_type {
	OT_PLAYER,
	OT_METEOR,
	OT_ENEMY,
	OT_NONE
};

class game_object : public renderable, public movable {
public:
	game_object(object_type in_object_type);
	game_object(point &initial_point);
	game_object(float initial_x, float initial_y, move_direction in_move_dir = move_direction::MD_NONE);

	virtual ~game_object() {}

	void update		(float delta_time);

	virtual void draw(const shader_program &in_shader) override;

	void set_position	(float in_x, float in_y);
	void set_position	(point &in_position);
	const point &get_position	() const {	return m_position;	}

	point get_move_dir() const;

	float m_direction = 0.f;

private:
	object_type m_type;
	float m_velocity = 300.f;
	point m_position;

};
#endif // GAME_OBJECT_H