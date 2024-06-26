#ifndef CONTROLLABLE_H
#define CONTROLLABLE_H

class controllable {
public:
	virtual ~controllable() {}

	virtual void move_forward	()	= 0;
	virtual void move_right		()	= 0;
	virtual void move_backward	()	= 0;
	virtual void move_left		()	= 0;
	virtual void shoot			()	= 0;

	virtual void reset_movement	()	= 0;
};
#endif // CONTROLLABLE_H