#ifndef METEOR_H
#define METEOR_H

#include "game_object.h"
#include "movable.h"

class meteor : public game_object, public movable {
	using	parent = game_object;
public:
	meteor(const vector2f &initial_point, const vector2f &in_forward_vector);
	virtual ~meteor() {}

	virtual void update(float delta_time) override;
};
#endif // METEOR_H
