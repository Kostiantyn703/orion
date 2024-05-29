#ifndef MOVABLE_H
#define MOVABLE_H

#include "../utils/globals.h"

class movable {
protected:
	movable() : m_velocity(0.f), m_move_dir(0.f, 0.f), m_forward_vector(0.f, 0.f) {}
	virtual ~movable() {}

	void set_move_dir(vector2f in_move_dir) { m_move_dir = in_move_dir; }
	vector2f get_move_dir()	const { return m_move_dir; }
	
	void set_forward_vector(vector2f in_forward_vector) { m_forward_vector = in_forward_vector; }
	vector2f get_forward_vector() const { return m_forward_vector; }

	void set_velocity(float in_velocity) { m_velocity = in_velocity; }
	float get_velocity() const { return m_velocity; }

	void merge_movement(vector2f &in_vector) { m_move_dir = m_move_dir + in_vector; }
private:
	float m_velocity;
	vector2f m_move_dir;
	vector2f m_forward_vector;
};
#endif // MOVABLE_H
