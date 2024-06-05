#ifndef BORDER_H
#define BORDER_H

#include "../interfaces/collidable.h"
#include "../utils/globals.h"

class border : public collidable {
public:
	border() : side(border_side::BS_NONE) {}
	virtual ~border() {}

	border_side	get_side()	const { return side; }
	void		set_side(border_side side) { this->side = side; }

	virtual bool on_intersect() { return false; };
	virtual void borders_intersect(border_side side) {};

private:
	border_side side;
};

#endif // BORDER_H
