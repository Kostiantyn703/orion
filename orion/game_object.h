#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "globals.h"
#include "renderable.h"
#include "collidable.h"

class game_object : public renderable, public collidable {
public:
	game_object(const vector2f &initial_point);
	virtual ~game_object();

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
protected:
	void set_origin(float in_x, float in_y);
	void set_origin(const vector2f &in_position);
	const vector2f	&get_origin() const { return m_origin; }

	const vector2f	&get_size() const { return m_size; }

private:
	bool to_remove = false;
	
	vector2f m_origin;
	vector2f m_size;
};
#endif // GAME_OBJECT_H