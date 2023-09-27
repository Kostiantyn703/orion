#include "shader_program.h"

shader_program::shader_program() {
	create();
}

shader_program::~shader_program() {}

void shader_program::use() {
	glUseProgram(m_id);
}

void shader_program::attach_shader(GLuint shader_id) {
	glAttachShader(m_id, shader_id);
}

void shader_program::link() {
	glLinkProgram(m_id);
}

void shader_program::create() {
	m_id = glCreateProgram();
	// TODO: error log check
}