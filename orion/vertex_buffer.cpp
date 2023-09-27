#include "vertex_buffer.h"

vertex_buffer::vertex_buffer() {
	create();
}

vertex_buffer::~vertex_buffer() {}

void vertex_buffer::init_data() {
	// create buffer data
	float vertices[] = {
		-0.5f, -0.5f, 0.0f, // left  
		 0.5f, -0.5f, 0.0f, // right 
		 0.0f,  0.5f, 0.0f  // top   
	};
	bind();
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
}

void vertex_buffer::bind() {
	glBindBuffer(GL_ARRAY_BUFFER, m_id);
}

void vertex_buffer::unbind() {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void vertex_buffer::create() {
	glGenBuffers(1, &m_id);
	
}