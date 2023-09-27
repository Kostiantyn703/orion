#include "vertex_array.h"

vertex_array::vertex_array() {
	create();
}

vertex_array::~vertex_array() {}

void vertex_array::init_data() {
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
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
