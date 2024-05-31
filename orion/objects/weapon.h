#ifndef WEAPON_H
#define WEAPON_H

#include "../utils/globals.h"

class weapon {
public:
	weapon() : can_shoot(true), reload_timer(0.f), max_reload_time(WEAPON_RELOAD_TIME), position(0.f, 0.f) {}

	void set_can_shoot(bool val) { can_shoot = val; }
	float get_can_shoot() const { return can_shoot; }

	void set_postition(const vector2f &position) { this->position = position; }
	vector2f get_position() const { return position; }

	void reset_reload_timer() { reload_timer = max_reload_time; }
	float get_reload_timer() const { return reload_timer; }

	void decrease_reload_timer(float delta_time) { reload_timer -= delta_time; }
private:
	bool can_shoot;
	float reload_timer;
	float max_reload_time;

	vector2f position;
};
#endif // WEAPON_H
