#ifndef RENDERABLE_H
#define RENDERABLE_H

class shader_program;
class texture;

class renderable {
public:
	virtual ~renderable() {}
	virtual void draw(const shader_program &shader) = 0;
	virtual void set_texture(texture *tex) = 0;

protected:
	texture	*get_texture() const { return tex; }

	texture	*tex = nullptr;
};
#endif // RENDERABLE_H
