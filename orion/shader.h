#ifndef SHADER_H
#define SHADER_H

#include "glad/glad.h"
#include "SDL_opengl.h"

class shader {
public:
	shader(const char *shader_source, GLenum shader_type);
	~shader();

	GLuint get_id() const { return m_id; }

	bool compile();
	void destroy();

private:
	GLuint m_id;

	void create(const char *shader_source, GLenum shader_type);
	bool log_errors();

	shader() = delete;
};
#endif // SHADER_H
