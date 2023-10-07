#include "vertex_array.h"

vertex_array::vertex_array() {
	create();
}

vertex_array::~vertex_array() {}

void vertex_array::init_data() {
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
	glEnableVertexAttribArray(1);

	GLuint offset_loc =  glGetUniformLocation(m_id, "offset");
	glUniform2f(offset_loc, 0.f, 0.f);
}

void vertex_array::bind() {
	glBindVertexArray(m_id);
}

void vertex_array::unbind() {
	glBindVertexArray(0);
}

void vertex_array::create() {
	glGenVertexArrays(1, &m_id);
}
