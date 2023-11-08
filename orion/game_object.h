#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "globals.h"

#include "controllable.h"
#include "movable.h"
#include "renderable.h"

enum class object_type {
	OT_PLAYER,
	OT_METEOR,
	OT_ENEMY,
	OT_BULLET,
	OT_NONE
};

class game_object : public controllable, public movable, public renderable {
public:
	game_object(const point &initial_point);
	game_object(float initial_x, float initial_y);

	virtual ~game_object() {}

	void update		(float delta_time);

	virtual void draw(const shader_program &in_shader) override;

	void set_position	(float in_x, float in_y);
	void set_position	(point &in_position);
	const point &get_position	() const {	return m_position;	}

	void set_velocity	(float in_velocity)		{	m_velocity = in_velocity;	}
	void set_type		(object_type in_type)	{	m_type = in_type;			}
	// ~ controllable interface
	virtual void move_forward	()	override;
	virtual void move_right		()	override;
	virtual void move_backward	()	override;
	virtual void move_left		()	override;
	virtual void shoot			()	override;
	// ~ end controllable interface
private:
	float m_velocity = 750.f;
	float m_direction = 0.f;
	
	point m_position;
	point m_move_dir;

	object_type m_type;
};
#endif // GAME_OBJECT_H