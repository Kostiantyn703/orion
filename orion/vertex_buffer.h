#ifndef VERTEX_BUFFER_H
#define VERTEX_BUFFER_H

#include "glad/glad.h"

class vertex_buffer {
public:
	vertex_buffer();
	~vertex_buffer();

	void init_data();

	void bind();
	void unbind();

private:
	GLuint m_id;

	void create();
};
#endif // VERTEX_BUFFER_H
