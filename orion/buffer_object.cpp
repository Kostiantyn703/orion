#include "buffer_object.h"

buffer_object::buffer_object(unsigned int in_target)
	: m_target(in_target)
{
	create();
}

buffer_object::~buffer_object() {
	glDeleteBuffers(1, &m_id);
}

void buffer_object::bind() {
	glBindBuffer(m_target, m_id);
}

void buffer_object::unbind() {
	glBindBuffer(m_target, 0);
}

void buffer_object::create() {
	glGenBuffers(1, &m_id);
}