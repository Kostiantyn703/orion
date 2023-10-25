#ifndef RENDERABLE_H
#define RENDERABLE_H

#include <memory>

#include "globals.h"

#include "shader_program.h"
#include "vertex_array.h"
#include "texture.h"
#include "buffer_object.h"

struct render_data {
	texture			*m_texture = nullptr;
	
	std::unique_ptr<shader_program>	m_shader_program;
	std::unique_ptr<vertex_array>	m_vertex_array;
	
	std::unique_ptr<buffer_object>	m_vertex_buffer;
	std::unique_ptr<buffer_object>	m_element_buffer;
};

class renderable {
public:
	virtual ~renderable() {}

	void init(const std::string &in_vertex_source, const std::string &in_fragment_source);

	void set_texture	(texture &in_texture)	{	m_render_data.m_texture = &in_texture;}

	virtual void draw() = 0;

protected:
	render_data m_render_data;
	
};
#endif // RENDERABLE_H
