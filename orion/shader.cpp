#include "shader.h"

#include "SDL_log.h"
#include <vector>

shader::shader(const char *shader_source, GLenum shader_type) {
	create(shader_source, shader_type);
}

shader::~shader() {}

void shader::create(const char *shader_source, GLenum shader_type) {
	m_id = glCreateShader(shader_type);
	glShaderSource(m_id, 1, &shader_source, nullptr);
}

bool shader::compile() {
	glCompileShader(m_id);
	if (!log_errors()) {
		return false;
	}
	return true;
}

void shader::destroy() {
	glDeleteShader(m_id);
}

bool shader::log_errors() {
	GLint success = 0;
	glGetShaderiv(m_id, GL_COMPILE_STATUS, &success);
	if (!success) {
		GLint log_size = 0;
		glGetShaderiv(m_id, GL_INFO_LOG_LENGTH, &log_size);
		std::vector<GLchar> info_log(log_size);
		glGetShaderInfoLog(m_id, log_size, &log_size, &info_log[0]);
		SDL_Log(&info_log[0]);
		return false;
	}
	return true;
}
