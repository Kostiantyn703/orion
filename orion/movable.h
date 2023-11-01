#ifndef MOVABLE_H
#define MOVABLE_H

enum class move_direction {
	MD_UP,
	MD_RIGHT,
	MD_DOWN,
	MD_LEFT,
	MD_NONE
};

enum class look_direction {
	LD_UP,
	LD_RIGHT,
	LD_DOWN,
	LD_LEFT,
	LD_NONE
};

class movable {
public:
	virtual ~movable() {}

	void set_move_dir(move_direction in_move_dir)	{	m_move_dir = in_move_dir;	}
	void set_look_dir(look_direction in_look_dir)	{	m_look_dir = in_look_dir;	}
protected:
	move_direction m_move_dir;
	look_direction m_look_dir;
};
#endif // MOVABLE_H