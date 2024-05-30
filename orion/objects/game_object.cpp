#include "game_object.h"

#include <SDL_log.h>
#include "glad/glad.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "../interfaces/subscriber.h"

#include "../render/texture.h"
#include "../render/shader_program.h"

game_object::game_object(const vector2f &initial_point) : to_remove(false), m_rotation(0.f), m_score(0) {
	set_origin(initial_point);
}

void game_object::update(float delta_time) {
	vector2f delta_vec = get_move_dir() * get_velocity() * delta_time;
	set_origin(get_origin() + delta_vec);
	set_center(get_center() + delta_vec);
	m_aabb.calculate(get_origin(), get_size(), SIZE_SCALAR);
}

void game_object::draw(const shader_program &in_shader) {
	// draw texture
	glm::mat4 model = glm::mat4(1.f);
	glm::vec2 model_size(m_size.get_x(), m_size.get_y());
	model = glm::translate(model, glm::vec3(m_origin.get_x() + m_size.get_x() * 0.5f, m_origin.get_y() + m_size.get_y() * 0.5f, 0.f));
	model = glm::rotate(model, glm::radians(m_rotation), glm::vec3(0.f, 0.f, 1.f));
	model = glm::translate(model, glm::vec3(-m_size.get_x() * 0.5f, -m_size.get_y() * 0.5f, 0.f));
	model = glm::scale(model, glm::vec3(model_size, 1.0f));
	glUniformMatrix4fv(glGetUniformLocation(in_shader.id(), "model"), 1, false, glm::value_ptr(model));
	glUniform2f(glGetUniformLocation(in_shader.id(), "scalar"), 1.f, 1.f);
	glUniform1f(glGetUniformLocation(in_shader.id(), "scroll"), 0.f);
	// draw aabb
	glm::mat4 aabb = glm::mat4(1.f);
	aabb = glm::translate(aabb, glm::vec3(m_aabb.get_origin().get_x(), m_aabb.get_origin().get_y(), 0.f));
	glm::vec2 aabb_size(m_aabb.get_size().get_x(), m_aabb.get_size().get_y());
	aabb = glm::scale(aabb, glm::vec3(aabb_size, 1.0f));
	glUniformMatrix4fv(glGetUniformLocation(in_shader.id(), "aabb_model"), 1, false, glm::value_ptr(aabb));
	
	glActiveTexture(GL_TEXTURE0);
	m_texture->bind();
}

void game_object::set_texture(texture *in_texture) {
	m_texture = in_texture;
	m_size.set_x((float)m_texture->get_width());
	m_size.set_y((float)m_texture->get_height());
}

void game_object::set_origin(float in_x, float in_y) {
	m_origin.set_x(in_x);
	m_origin.set_y(in_y);
}

void game_object::set_origin(const vector2f &in_position) {
	m_origin = in_position;
}

void game_object::set_center(const vector2f &in_pos) {
	m_center = in_pos;
}

bool game_object::on_intersect() {
	set_to_remove(true);
	return false;
}

void game_object::recalc_pos() {
	vector2f pos = get_origin();
	set_center(pos);
	float x_pos = pos.get_x() - get_size().get_x() * 0.5f;
	float y_pos = pos.get_y() - get_size().get_y() * 0.5f;
	set_origin(x_pos, y_pos);
}
