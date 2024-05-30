#ifndef BORDER_H
#define BORDER_H

#include "../interfaces/collidable.h"
#include "../utils/globals.h"

class border : public collidable {
public:
	border() : m_side(border_side::BS_NONE) {}
	virtual ~border() {}

	border_side	get_side()	const { return m_side; }
	void		set_side(border_side in_side) { m_side = in_side; }

	virtual bool on_intersect() { return false; };
	virtual void borders_intersect(border_side in_side) {};

private:
	border_side m_side;
};

#endif // BORDER_H
