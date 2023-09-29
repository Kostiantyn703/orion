#include "buffer_object.h"


buffer_object::buffer_object(GLuint in_target)
	: m_target(in_target)
{
	create();
}

buffer_object::~buffer_object() {}

void buffer_object::bind() {
	glBindBuffer(m_target, m_id);
}

void buffer_object::unbind() {
	glBindBuffer(m_target, 0);
}

void buffer_object::create() {
	glGenBuffers(1, &m_id);
}