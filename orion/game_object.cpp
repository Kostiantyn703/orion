#include "game_object.h"

#include <SDL_log.h>
#include "glad/glad.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "texture.h"
#include "shader_program.h"

game_object::game_object(point &initial_point) {
	set_position(initial_point.x_pos, initial_point.y_pos);
	m_move_dir = move_direction::MD_NONE;
}

game_object::game_object(float initial_x, float initial_y, move_direction in_move_dir) {
	set_position(initial_x, initial_y);
	m_move_dir = in_move_dir;
}

void game_object::update(float delta_time) {
	point curr_pos = get_position();
	point curr_dir = get_move_dir();

	curr_pos.x_pos += curr_dir.x_pos * delta_time * m_velocity;
	curr_pos.y_pos += curr_dir.y_pos * delta_time * m_velocity;

	m_direction += delta_time * m_velocity;

	set_position(curr_pos.x_pos, curr_pos.y_pos);
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

point game_object::get_move_dir() const {
	point result(0.f, 0.f);
	switch (m_move_dir) {
		case move_direction::MD_UP:
			result.y_pos = -1.f;
		break;
		case move_direction::MD_RIGHT:
			result.x_pos = 1.f;
		break;
		case move_direction::MD_DOWN:
			result.y_pos = 1.f;
		break;
		case move_direction::MD_LEFT:
			result.x_pos = -1.f;
		break;
	}
	return result;
}
