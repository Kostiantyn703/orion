#include "shader.h"

#include <vector>
#include "glad/glad.h"
#include "SDL_log.h"

shader::shader(const char *shader_source, const unsigned int shader_type) {
	m_id = glCreateShader(shader_type);
	glShaderSource(m_id, 1, &shader_source, nullptr);
}

bool shader::compile() {
	glCompileShader(m_id);
	if (!log_errors(GL_COMPILE_STATUS)) {
		return false;
	}
	return true;
}

void shader::destroy() {
	glDeleteShader(m_id);
}

bool shader::log_errors(const unsigned int check_type) {
	int success = 0;
	glGetShaderiv(m_id, check_type, &success);
	if (!success) {
		int log_size = 0;
		glGetShaderiv(m_id, GL_INFO_LOG_LENGTH, &log_size);
		std::vector<char> info_log(log_size);
		glGetShaderInfoLog(m_id, log_size, &log_size, &info_log[0]);
		SDL_Log(&info_log[0]);
		return false;
	}
	return true;
}
