#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "globals.h"

#include "controllable.h"
#include "movable.h"
#include "renderable.h"
#include "collidable.h"
#include "weapon.h"

class subscriber;

enum class object_type {
	OT_PLAYER,
	OT_METEOR,
	OT_ENEMY,
	OT_BULLET,
	OT_NONE
};

class game_object : public controllable, public movable, public renderable, public collidable {
public:
	game_object(vector2f &initial_point);
	game_object(float initial_x, float initial_y);

	virtual ~game_object();

	void update		(float delta_time);
	// ~ renderable interface
	virtual void draw(const shader_program &in_shader) override;
	virtual void set_texture(texture *in_texture) override;
	// ~ end renderable interface

	void set_to_remove			(bool in_val)	{	to_remove = in_val;	}
	bool should_remove			()	const		{	return to_remove;	}

	void set_origin				(float in_x, float in_y);
	void set_origin				(const vector2f &in_position);
	const vector2f	&get_origin	() const {	return m_origin;	}

	void set_type		(object_type in_type)		{	m_type = in_type;			}

	void subscribe		(subscriber *in_listener)	{	m_listener = in_listener;	}

	// ~ controllable interface
	virtual void move_forward	()	override;
	virtual void move_right		()	override;
	virtual void move_backward	()	override;
	virtual void move_left		()	override;
	virtual void shoot			()	override;
	// ~ end controllable interface

	// ~ collidable interface
	virtual void on_intersect	()	override;
	// ~ end collidable interface
private:
	bool to_remove = false;
	float m_direction = 0.f;
	
	vector2f m_origin;
	vector2f m_size;
	vector2f m_move_dir;

	object_type m_type;

	weapon *m_weapon;

	subscriber *m_listener = nullptr;
};
#endif // GAME_OBJECT_H