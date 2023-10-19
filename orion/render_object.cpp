#include "render_object.h"
#include "shader.h"
#include "globals.h"

render_object::render_object() {}

render_object::~render_object() {}

void render_object::init(const std::string &in_vertex_source, const std::string &in_fragment_source) {
	
	std::unique_ptr<shader> vert = std::make_unique<shader>(in_vertex_source.data(), GL_VERTEX_SHADER);
	vert->compile();

	std::unique_ptr<shader> frag = std::make_unique<shader>(in_fragment_source.data(), GL_FRAGMENT_SHADER);
	frag->compile();

	m_shader_program = std::make_unique<shader_program>();
	m_shader_program->attach_shader(vert->get_id());
	m_shader_program->attach_shader(frag->get_id());
	m_shader_program->link();

	vert->destroy();
	frag->destroy();

	m_vertex_array = std::make_unique<vertex_array>();
	m_vertex_buffer = std::make_unique<buffer_object>(GL_ARRAY_BUFFER);
	m_element_buffer = std::make_unique<buffer_object>(GL_ELEMENT_ARRAY_BUFFER);

	m_vertex_array->bind();

	m_vertex_buffer->init_data(vertices);
	m_element_buffer->init_data(indices);
	m_vertex_array->init_data();

	m_vertex_buffer->unbind();
	m_vertex_array->unbind();
}

void render_object::draw() {
	m_texture->bind();
	m_shader_program->use();
	m_vertex_array->bind();
}
