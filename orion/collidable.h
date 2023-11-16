#ifndef COLLIDABLE_H
#define COLLIDABLE_H

#include "globals.h"
#include <cstdint>

constexpr float SIZE_SCALAR = 0.2f;

class aabb {
public:
	aabb() : m_origin(0.f, 0.f), m_size(0.f, 0.f) {}
	~aabb() {}

	void		set_origin(const vector2f &in_origin) { m_origin = in_origin; }
	vector2f	get_origin()	const { return m_origin; }
	void		set_size(const vector2f &in_size) { m_size = in_size; }
	vector2f	get_size()	const { return m_size; }

	void calculate(vector2f &in_origin, vector2f &in_size) {
		vector2f aabb_origin = in_origin + (in_size * SIZE_SCALAR);
		set_origin(aabb_origin);
		vector2f aabb_size = in_size * (1.f - (SIZE_SCALAR * 2));
		set_size(aabb_size);
	}

private:
	vector2f	m_origin;
	vector2f	m_size;
};
// collision masks
constexpr std::uint8_t MASK_PLAYER			= 1 << 0;
constexpr std::uint8_t MASK_PLAYER_BULLET	= 1 << 1;
constexpr std::uint8_t MASK_ENEMY			= 1 << 2;
constexpr std::uint8_t MASK_ENEMY_BULLET	= 1 << 3;

class collidable {
public:
	virtual ~collidable() {}
	virtual void on_intersect() = 0;

	const aabb &get_aabb() const { return m_aabb; }
	void set_mask(uint8_t in_mask) { m_mask = in_mask; }
	const std::uint8_t get_mask() const { return m_mask; }
protected:
	aabb m_aabb;
	std::uint8_t m_mask;
};

#endif //COLLIDABLE_H