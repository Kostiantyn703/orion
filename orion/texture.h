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

	void init_data(unsigned char *in_data, const GLint &in_width, const GLint &in_height, const GLint &in_channels);

private:
	GLuint m_id;
	GLuint m_target;
	GLuint m_format;

	GLint m_width;
	GLint m_height;
	GLint m_channels;

	void create();
};
#endif // TEXTURE_H
