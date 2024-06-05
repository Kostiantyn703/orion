#ifndef COLLIDABLE_H
#define COLLIDABLE_H

#include <cstdint>
#include "../utils/globals.h"

class aabb {
public:
	aabb() : origin(0.f, 0.f), size(0.f, 0.f) {}
	aabb(const vector2f origin, const vector2f size) {
		this->origin = origin;
		this->size = size;
	}

	void set_origin(const vector2f &origin) { this->origin = origin; }
	vector2f get_origin()	const { return origin; }
	void set_size(const vector2f &size) { this->size = size; }
	vector2f get_size()	const { return size; }

	void calculate(const vector2f &origin, const vector2f &size) {
		vector2f aabb_origin = origin + (size * SIZE_SCALAR);
		set_origin(aabb_origin);
		vector2f aabb_size = size * (1.f - (SIZE_SCALAR * 2));
		set_size(aabb_size);
	}

private:
	vector2f origin;
	vector2f size;
};

// collision masks
constexpr std::uint8_t MASK_PLAYER			= 1 << 0;
constexpr std::uint8_t MASK_PLAYER_BULLET	= 1 << 1;
constexpr std::uint8_t MASK_ENEMY			= 1 << 2;
constexpr std::uint8_t MASK_ENEMY_BULLET	= 1 << 3;
constexpr std::uint8_t MASK_BORDER			= 1 << 4;

class collidable {
public:
	virtual ~collidable() {}
	virtual bool on_intersect() = 0;
	virtual void borders_intersect(border_side side) {};

	const aabb &get_aabb() const { return box;	}
	void set_aabb(const aabb &box) { this->box = box;	}

	void set_mask(uint8_t mask) { this->mask = mask;	}
	const std::uint8_t get_mask() const	{ return mask;	}
protected:
	aabb box;
	std::uint8_t mask;
};
#endif //COLLIDABLE_H
