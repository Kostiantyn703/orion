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

	void init_data(unsigned char *in_data, const int &in_width, const int &in_height, const int &in_channels);

private:
	GLuint m_id;
	GLuint m_target;
	GLuint m_format;

	int m_width;
	int m_height;
	int m_channels;

	void create();
};
#endif // TEXTURE_H
