#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "globals.h"
#include "renderable.h"
#include "collidable.h"
#include "controller.h"
#include "movable.h"

class game_object : public renderable, public collidable, public movable{
public:
	game_object(const vector2f &initial_point);
	virtual ~game_object();

	virtual void init() {}
	// for spaceship
	virtual void on_spawn() {}
	virtual void on_remove(bool &in_val) {}
	// TODO: maybe pure virtual
	virtual void update		(float delta_time);
	// ~ renderable interface
	virtual void draw(const shader_program &in_shader) override;
	virtual void set_texture(texture *in_texture) override;
	// ~ end renderable interface

	void set_to_remove			(bool in_val)	{	to_remove = in_val;	}
	bool should_remove			()	const		{	return to_remove;	}

	// ~ collidable interface
	virtual void on_intersect	()	override;
	// ~ end collidable interface

	const vector2f	&get_origin	()	const	{	return m_origin;	}
			vector2f *get_origin_ptr() { return &m_origin; }
	const vector2f	&get_size	()	const	{	return m_size;		}
	const vector2f	&get_center	()	const	{	return m_center;	}

	void set_rotation(float in_rotation) { m_rotation = in_rotation; }
	float get_rotation() const { return m_rotation; }

protected:
	void set_origin(float in_x, float in_y);
	void set_origin(const vector2f &in_position);

	void set_center(const vector2f &in_pos);

	void recalc_pos();



private:
	bool		to_remove	= false;
	float		m_rotation	= 0.f;
	vector2f	m_origin;
	vector2f	m_size;
	vector2f	m_center;
};
#endif // GAME_OBJECT_H