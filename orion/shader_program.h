#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H

#include "glad/glad.h"

class shader_program {
public:
	shader_program();
	~shader_program();

	GLuint id()	{	return m_id;	}

	void use();
	void attach_shader(const GLuint shader_id);
	void link();

private:
	GLuint m_id;

	void create();
};
#endif // SHADER_PROGRAM_H
