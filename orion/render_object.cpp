#include "render_object.h"
#include "shader.h"
#include "globals.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"


render_object::render_object() {}

render_object::~render_object() {}

void render_object::set_position(const point &in_pos) {
	m_position = in_pos;
}

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
	m_shader_program->use();

	glm::mat4 model = glm::mat4(1.f);

	float actual_x = m_position.x_pos - m_texture->get_width();
	float actual_y = m_position.y_pos - m_texture->get_height();
	model = glm::translate(model, glm::vec3(actual_x, actual_y, 0.f));
	glm::vec2 size(m_texture->get_width(), m_texture->get_height());
	model = glm::translate(model, glm::vec3(size.x, size.y, 0.f));

	model = glm::scale(model, glm::vec3(size * 0.5f, 1.0f));
	glUniformMatrix4fv(glGetUniformLocation(m_shader_program->id(), "model"), 1, false, glm::value_ptr(model));

	glm::mat4 projection = glm::ortho(0.f, WINDOW_WIDTH, WINDOW_HEIGHT, 0.f, -1.f, 1.f);
	glUniformMatrix4fv(glGetUniformLocation(m_shader_program->id(), "projection"), 1, false, glm::value_ptr(projection));

	m_texture->bind();
	m_vertex_array->bind();
}
