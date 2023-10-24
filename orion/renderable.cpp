#include "renderable.h"
#include "shader.h"
#include "globals.h"

void renderable::init(const std::string &in_vertex_source, const std::string &in_fragment_source) {
	std::unique_ptr<shader> vert = std::make_unique<shader>(in_vertex_source.data(), GL_VERTEX_SHADER);
	vert->compile();

	std::unique_ptr<shader> frag = std::make_unique<shader>(in_fragment_source.data(), GL_FRAGMENT_SHADER);
	frag->compile();

	m_render_data.m_shader_program = std::make_unique<shader_program>();
	m_render_data.m_shader_program->attach_shader(vert->get_id());
	m_render_data.m_shader_program->attach_shader(frag->get_id());
	m_render_data.m_shader_program->link();

	vert->destroy();
	frag->destroy();

	m_render_data.m_vertex_array = std::make_unique<vertex_array>();
	m_render_data.m_vertex_buffer = std::make_unique<buffer_object>(GL_ARRAY_BUFFER);
	m_render_data.m_element_buffer = std::make_unique<buffer_object>(GL_ELEMENT_ARRAY_BUFFER);

	m_render_data.m_vertex_array->bind();

	m_render_data.m_vertex_buffer->init_data(vertices);
	m_render_data.m_element_buffer->init_data(indices);
	m_render_data.m_vertex_array->init_data();

	m_render_data.m_vertex_buffer->unbind();
	m_render_data.m_vertex_array->unbind();
}
