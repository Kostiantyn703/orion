#ifndef RENDER_OBJECT_H
#define RENDER_OBJECT_H

#include <memory>

#include "globals.h"

#include "shader_program.h"
#include "vertex_array.h"
#include "texture.h"
#include "buffer_object.h"

class render_object {
public:
	render_object();
	~render_object();

	void init(const std::string &in_vertex_source, const std::string &in_fragment_source);

	void set_position	(const point &in_pos);
	void set_texture	(texture &in_texture)	{	m_texture = std::make_unique<texture>(in_texture);}

	void draw();

private:
	std::unique_ptr<shader_program>	m_shader_program;
	std::unique_ptr<vertex_array>	m_vertex_array;
	std::unique_ptr<texture>		m_texture;
	std::unique_ptr<buffer_object>	m_vertex_buffer;
	std::unique_ptr<buffer_object>	m_element_buffer;

	point m_position;
};
#endif //RENDER_OBJECT_H
