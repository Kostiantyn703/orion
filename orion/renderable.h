#ifndef RENDERABLE_H
#define RENDERABLE_H

class shader_program;
class texture;

class renderable {
public:
	virtual ~renderable() {}
	virtual void draw(const shader_program &in_shader) = 0;
	void set_texture(texture *in_texture)	{	m_texture = in_texture;}
protected:
	texture	*m_texture = nullptr;
};
#endif // RENDERABLE_H
