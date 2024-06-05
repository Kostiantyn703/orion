#include "buffer_object.h"

buffer_object::buffer_object(unsigned int target) {
	this->target = target;
	create();
}

buffer_object::~buffer_object() {
	glDeleteBuffers(1, &id);
}

void buffer_object::bind() {
	glBindBuffer(target, id);
}

void buffer_object::unbind() {
	glBindBuffer(target, 0);
}

void buffer_object::create() {
	glGenBuffers(1, &id);
}