#ifndef BORDER_H
#define BORDER_H

#include "collidable.h"
#include "globals.h"

class border : public collidable {
public:
	border() : m_side(border_side::BS_NONE) {}
	~border() {}

	border_side	get_side()	const { return m_side; }
	void		set_side(border_side in_side) { m_side = in_side; }

	virtual void on_intersect() {};
	virtual void borders_intersect(border_side in_side) {};

private:
	border_side m_side;
};

#endif // BORDER_H
