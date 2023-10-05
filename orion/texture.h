#ifndef TEXTURE_H
#define TEXTURE_H

#include "glad/glad.h"

class texture {
public:
	texture();
	~texture();

	GLuint id() const { return m_id;}

	void bind();
	void unbind();

private:
	GLuint m_id;

	void create();
};

#endif // TEXTURE_H
