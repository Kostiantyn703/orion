#include "game_object.h"

#include <SDL_log.h>
#include "glad/glad.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "texture.h"
#include "shader_program.h"
#include "subscriber.h"

game_object::game_object(const vector2f &initial_point) {
	set_origin(initial_point);
	m_move_dir.set_x(0.f);
	m_move_dir.set_y(0.f);
}

game_object::game_object(float initial_x, float initial_y) {
	set_origin(initial_x, initial_y);
	m_move_dir.set_x(0.f);
	m_move_dir.set_y(0.f);
}

void game_object::update(float delta_time) {
	vector2f delta_vec = m_move_dir * delta_time;
	m_origin = m_origin + delta_vec;
	m_aabb.calculate(m_origin, m_size);
	// TODO: temporary borders
	if (m_origin.get_x() < 0.f) {
		m_origin.set_x(1.f);
	}
	if (m_origin.get_x() > WINDOW_WIDTH) {
		m_origin.set_x(WINDOW_WIDTH - 1.f);
	}

	if (!can_shoot) {
		m_reload_timer -= delta_time;
		if (m_reload_timer < 0.f) {
			can_shoot = true;
		}
	}
	// TODO: temporary
	if (m_type != object_type::OT_BULLET) {
		m_move_dir.set_x(0.f);
		m_move_dir.set_y(0.f);
	}
	if (m_type == object_type::OT_BULLET) {
		if (m_origin.get_y() < 0.f) {
			to_remove = true;
		}
	}
}

void game_object::draw(const shader_program &in_shader) {
	glm::mat4 model = glm::mat4(1.f);
	glm::mat4 aabb = glm::mat4(1.f);
	model = glm::translate(model, glm::vec3(m_origin.get_x(), m_origin.get_y(), 0.f));
	aabb = glm::translate(aabb, glm::vec3(m_aabb.get_origin().get_x(), m_aabb.get_origin().get_y(), 0.f));
	
	//model = glm::rotate(model, glm::radians(m_direction), glm::vec3(0.f, 0.f, 1.f));

	glm::vec2 model_size(m_size.get_x(), m_size.get_y());
	glm::vec2 aabb_size(m_aabb.get_size().get_x(), m_aabb.get_size().get_y());
	model = glm::scale(model, glm::vec3(model_size, 1.0f));
	aabb = glm::scale(aabb, glm::vec3(aabb_size, 1.0f));

	glUniformMatrix4fv(glGetUniformLocation(in_shader.id(), "model"), 1, false, glm::value_ptr(model));
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

void game_object::move_forward() {
	m_move_dir.set_y(-1);
}

void game_object::move_right() {
	m_move_dir.set_x(1);
}

void game_object::move_backward() {
	m_move_dir.set_y(1);
}

void game_object::move_left() {
	m_move_dir.set_x(-1);
}

void game_object::shoot() {
	if (can_shoot) {
		m_listener->on_notify(this);
		can_shoot = false;
		m_reload_timer = m_reload_max_time;
	}
}
