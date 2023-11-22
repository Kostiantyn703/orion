#ifndef MOVABLE_H
#define MOVABLE_H

class movable {
public:
	virtual ~movable() {}

	virtual void move_forward()		= 0;
	virtual void move_right()		= 0;
	virtual void move_backward()	= 0;
	virtual void move_left()		= 0;

protected:
	//vector2f m_move_dir;
	vector2f m_forward_vector;
};
#endif // MOVABLE_H
