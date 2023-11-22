#ifndef MOVABLE_H
#define MOVABLE_H

class movable {
protected:
	virtual		~movable()		{}

	void		set_move_dir	(vector2f in_move_dir)	{	m_move_dir = in_move_dir;	}
	vector2f	get_move_dir	()	const				{	return m_move_dir;			}
	
	void		set_forward_vector(vector2f in_forward_vector)	{	m_forward_vector = in_forward_vector;	}
	vector2f	get_forward_vector()	const					{	return m_forward_vector;				}
private:
	vector2f	m_move_dir;
	vector2f	m_forward_vector;
};
#endif // MOVABLE_H
