#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "globals.h"

#include "controllable.h"
#include "movable.h"
#include "renderable.h"

class subscriber;

enum class object_type {
	OT_PLAYER,
	OT_METEOR,
	OT_ENEMY,
	OT_BULLET,
	OT_NONE
};

class game_object : public controllable, public movable, public renderable {
public:
	game_object(const vector2f &initial_point);
	game_object(float initial_x, float initial_y);

	virtual ~game_object() {}

	void update		(float delta_time);
	// ~ renderable interface
	virtual void draw(const shader_program &in_shader) override;
	virtual void set_texture(texture *in_texture) override;
	// ~ end renderable interface

	void set_origin				(float in_x, float in_y);
	void set_origin				(vector2f &in_position);
	const vector2f &get_origin	() const {	return m_origin;	}

	void set_type		(object_type in_type)		{	m_type = in_type;			}

	void subscribe		(subscriber *in_listener)	{	m_listener = in_listener;	}

	// ~ controllable interface
	virtual void move_forward	()	override;
	virtual void move_right		()	override;
	virtual void move_backward	()	override;
	virtual void move_left		()	override;
	virtual void shoot			()	override;
	// ~ end controllable interface

	bool to_remove = false;
private:
	//float m_velocity = PLAYER_VELOCITY;
	float m_direction = 0.f;
	
	vector2f m_origin;
	vector2f m_move_dir;
	vector2f m_aabb;

	object_type m_type;

	subscriber *m_listener = nullptr;

	bool can_shoot = true;
	float m_reload_timer = 0.f;
	float m_reload_max_time = 300.f;
};
#endif // GAME_OBJECT_H