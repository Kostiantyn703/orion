#include "game_object.h"

#include <SDL_log.h>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "texture.h"
#include "shader_program.h"

game_object::game_object(point &initial_point) : m_direction(direction::D_NONE) {
	set_position(initial_point.x_pos, initial_point.y_pos);
}

game_object::game_object(float initial_x, float initial_y) : m_direction(direction::D_NONE) {
	set_position(initial_x, initial_y);
}

game_object::game_object(game_object &in_obj) {
	m_position = in_obj.m_position;
	m_direction = in_obj.m_direction;
	SDL_Log("Copy game object");
}

void game_object::update(float delta_time) {
	point curr_pos = get_position();
	point curr_dir = get_direction();

	curr_pos.x_pos += curr_dir.x_pos * delta_time * m_velocity;
	curr_pos.y_pos += curr_dir.y_pos * delta_time * m_velocity;

	set_position(curr_pos.x_pos, curr_pos.y_pos);
}

void game_object::draw(const shader_program &in_shader) {
	glm::mat4 model = glm::mat4(1.f);

	int curr_width = m_texture->get_width();
	int curr_height = m_texture->get_height();

	float actual_x = m_position.x_pos - curr_width;
	float actual_y = m_position.y_pos - curr_height;

	model = glm::translate(model, glm::vec3(actual_x, actual_y, 0.f));
	glm::vec2 size(curr_width, curr_height);
	model = glm::translate(model, glm::vec3(size.x, size.y, 0.f));

	model = glm::scale(model, glm::vec3(size * 0.5f, 1.0f));
	glUniformMatrix4fv(glGetUniformLocation(in_shader.id(), "model"), 1, false, glm::value_ptr(model));

	glm::mat4 projection = glm::ortho(0.f, WINDOW_WIDTH, WINDOW_HEIGHT, 0.f, -1.f, 1.f);
	glUniformMatrix4fv(glGetUniformLocation(in_shader.id(), "projection"), 1, false, glm::value_ptr(projection));

	m_texture->bind();
}

void game_object::set_position(float in_x, float in_y) {
	m_position.x_pos = in_x;
	m_position.y_pos = in_y; 
}

point game_object::get_direction() const {
	point result(0.f, 0.f);
	switch (m_direction) {
		case direction::D_UP:
			result.y_pos = -1.f;
		break;
		case direction::D_RIGHT:
			result.x_pos = 1.f;
		break;
		case direction::D_DOWN:
			result.y_pos = 1.f;
		break;
		case direction::D_LEFT:
			result.x_pos = -1.f;
		break;
	}
	return result;
}
