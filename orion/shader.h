#ifndef SHADER_H
#define SHADER_H

#include "glad/glad.h"
#include "SDL_opengl.h"

class shader {
public:
	shader()	{}
	~shader()	{}

	bool compile();
	void draw() const;


private:
	unsigned int VBO, VAO;

	unsigned int	m_vertex;
	unsigned int	m_fragment;
	unsigned int	m_program;

};

#endif SHADER_H
