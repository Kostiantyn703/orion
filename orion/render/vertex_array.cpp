#include "vertex_array.h"
#include "glad/glad.h"

vertex_array::vertex_array() {
	create();
}

void vertex_array::init_data() {
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
}

void vertex_array::bind() {
	glBindVertexArray(id);
}

void vertex_array::unbind() {
	glBindVertexArray(0);
}

void vertex_array::create() {
	glGenVertexArrays(1, &id);
}
