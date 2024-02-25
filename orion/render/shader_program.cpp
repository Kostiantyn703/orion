#include "shader_program.h"

#include "SDL.h"
#include "glad/glad.h"

shader_program::shader_program() {
	create();
}

void shader_program::use() {
	glUseProgram(m_id);
}

void shader_program::attach_shader(unsigned int shader_id) {
	glAttachShader(m_id, shader_id);
}

void shader_program::link() {
	glLinkProgram(m_id);
}

void shader_program::create() {
	m_id = glCreateProgram();
}