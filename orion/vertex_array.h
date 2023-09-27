#ifndef VERTEX_ARRAY_H
#define VERTEX_ARRAY_H

#include "glad/glad.h"

class vertex_array {
public:
	vertex_array();
	~vertex_array();

	void init_data();

	void bind();
	void unbind();

private:
	GLuint m_id;

	void create();
};
#endif // VERTEX_ARRAY_H
