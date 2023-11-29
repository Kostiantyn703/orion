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
}

game_object::~game_object() {

}

void game_object::update(float delta_time) {
}

void game_object::draw(const shader_program &in_shader) {
	// draw texture
	glm::mat4 model = glm::mat4(1.f);
	model = glm::translate(model, glm::vec3(m_origin.get_x(), m_origin.get_y(), 0.f));
	glm::vec2 model_size(m_size.get_x(), m_size.get_y());
	model = glm::scale(model, glm::vec3(model_size, 1.0f));
	glUniformMatrix4fv(glGetUniformLocation(in_shader.id(), "model"), 1, false, glm::value_ptr(model));
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
	// TODO: on bullet creation
	/*if (m_type == object_type::OT_BULLET) {
		m_origin.set_x(m_origin.get_x() - m_size.get_x() * 0.5f);
	}*/
}

void game_object::set_origin(float in_x, float in_y) {
	m_origin.set_x(in_x);
	m_origin.set_y(in_y);
}

void game_object::set_origin(const vector2f &in_position) {
	m_origin = in_position;
}

void game_object::on_intersect() {
	SDL_Log("I WAS COLLIDED!!!");
	set_to_remove(true);
}
