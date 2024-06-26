#ifndef BULLET_H
#define BULLET_H

#include "game_object.h"
#include "../interfaces/movable.h"

class bullet : public game_object {
public:
	bullet(const vector2f &initial_point, const vector2f &in_forward_vector);
	virtual ~bullet() {}

	virtual void update(float delta_time) override;

};
#endif // BULLET_H