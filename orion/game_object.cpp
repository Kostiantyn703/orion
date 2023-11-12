#include "game_object.h"

#include <SDL_log.h>
#include "glad/glad.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "texture.h"
#include "shader_program.h"
#include "subscriber.h"

game_object::game_object(const point &initial_point) {
	set_position(initial_point.x_pos, initial_point.y_pos);
	m_move_dir.x_pos = 0.f;
	m_move_dir.y_pos = 0.f;
}

game_object::game_object(float initial_x, float initial_y) {
	set_position(initial_x, initial_y);
	m_move_dir.x_pos = 0.f;
	m_move_dir.y_pos = 0.f;
}

void game_object::update(float delta_time) {
	m_position.x_pos += m_move_dir.x_pos * delta_time;
	m_position.y_pos += m_move_dir.y_pos * delta_time;
	// TODO: temporary borders
	if (m_position.x_pos < 0.f) {
		m_position.x_pos = 1.f;
	}
	if (m_position.x_pos > WINDOW_WIDTH) {
		m_position.x_pos = WINDOW_WIDTH - 1.f;
	}

	if (!can_shoot) {
		m_reload_timer -= delta_time;
		if (m_reload_timer < 0.f) {
			can_shoot = true;
		}
	}
	// TODO: temporary
	if (m_type != object_type::OT_BULLET) {
		m_move_dir.x_pos = 0.f;
		m_move_dir.y_pos = 0.f;
	}
	if (m_type == object_type::OT_BULLET) {
		if (m_position.y_pos < 0.f) {
			to_remove = true;
		}
	}
}

void game_object::draw(const shader_program &in_shader) {
	glm::mat4 model = glm::mat4(1.f);

	model = glm::translate(model, glm::vec3(m_position.x_pos, m_position.y_pos, 0.f));
	model = glm::rotate(model, glm::radians(m_direction), glm::vec3(0.f, 0.f, 1.f));

	float curr_width = (float)m_texture->get_width();
	float curr_height = (float)m_texture->get_height();
	float x_offset = curr_width * 0.5f;
	float y_offset = curr_height * 0.5f;
	model = glm::translate(model, glm::vec3(-x_offset, -y_offset, 0.f));

	glm::vec2 size(curr_width, curr_height);
	model = glm::scale(model, glm::vec3(size, 1.0f));

	glUniformMatrix4fv(glGetUniformLocation(in_shader.id(), "model"), 1, false, glm::value_ptr(model));
	glActiveTexture(GL_TEXTURE0);
	m_texture->bind();
}

void game_object::set_position(float in_x, float in_y) {
	m_position.x_pos = in_x;
	m_position.y_pos = in_y; 
}

void game_object::set_position(point &in_position) {
	m_position = in_position;
}

void game_object::move_forward() {
	m_move_dir.y_pos = -1;
}

void game_object::move_right() {
	m_move_dir.x_pos = 1;
}

void game_object::move_backward() {
	m_move_dir.y_pos = 1;
}

void game_object::move_left() {
	m_move_dir.x_pos = -1;
}

void game_object::shoot() {
	if (can_shoot) {
		m_listener->on_notify(this);
		can_shoot = false;
		m_reload_timer = m_reload_max_time;
	}
}
