#include "shader_program.h"

#include "SDL.h"
#include <complex>

shader_program::shader_program() {
	create();
}

shader_program::~shader_program() {}

void shader_program::use() {
	float curr_time = SDL_GetTicks() * 0.003f;
	float color_val = (0.7f * std::sin(curr_time)) + 0.5f;
	GLuint color_loc = glGetUniformLocation(id(), "shader_color");
	glUniform4f(color_loc, 0.f, 1.f - color_val, color_val, 1.f);

	float offset_x = 0.3f * (std::sin(curr_time * 0.5f));
	float offset_y = std::sin(curr_time) / 2.f;
	GLuint offset_loc = glGetUniformLocation(id(), "offset");
	glUniform2f(offset_loc, offset_x, offset_y);

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