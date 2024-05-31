#include "shader_program.h"

#include "glad/glad.h"

shader_program::shader_program() {
	create();
}

void shader_program::use() {
	glUseProgram(id);
}

void shader_program::attach_shader(unsigned int shader_id) {
	glAttachShader(id, shader_id);
}

void shader_program::link() {
	glLinkProgram(id);
}

void shader_program::create() {
	id = glCreateProgram();
}