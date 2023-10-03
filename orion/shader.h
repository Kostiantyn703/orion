#ifndef SHADER_H
#define SHADER_H

#include <vector>

#include "glad/glad.h"
#include "SDL_opengl.h"

class shader {
public:
	shader(const GLchar *shader_source, const GLenum shader_type);
	~shader();

	GLuint get_id() const { return m_id; }

	bool compile();
	void destroy();

private:
	GLuint m_id;

	bool log_errors();
	// TODO: move this method into factory class
	//void create(const std::string &shader_source, const GLenum shader_type);
	shader() = delete;
};
#endif // SHADER_H
