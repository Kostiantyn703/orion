#include "game_object.h"

#include <SDL_log.h>
#include "glad/glad.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "../interfaces/subscriber.h"

#include "../render/texture.h"
#include "../render/shader_program.h"

game_object::game_object(const vector2f &initial_point) : to_remove(false), rotation(0.f), score(0) {
	set_origin(initial_point);
}

void game_object::update(float delta_time) {
	vector2f delta_vec = get_direction() * get_velocity() * delta_time;
	set_origin(get_origin() + delta_vec);
	set_center(get_center() + delta_vec);
	box.calculate(get_origin(), get_size());
}

void game_object::draw(const shader_program &shader) {
	glm::mat4 model = glm::mat4(1.f);
	glm::vec2 model_size(size.get_x(), size.get_y());
	model = glm::translate(model, glm::vec3(origin.get_x() + size.get_x() * 0.5f, origin.get_y() + size.get_y() * 0.5f, 0.f));
	model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.f, 0.f, 1.f));
	model = glm::translate(model, glm::vec3(-size.get_x() * 0.5f, -size.get_y() * 0.5f, 0.f));
	model = glm::scale(model, glm::vec3(model_size, 1.0f));
	glUniformMatrix4fv(glGetUniformLocation(shader.get_id(), "model"), 1, false, glm::value_ptr(model));
	glUniform2f(glGetUniformLocation(shader.get_id(), "scalar"), 1.f, 1.f);
	glUniform1f(glGetUniformLocation(shader.get_id(), "scroll"), 0.f);

	glActiveTexture(GL_TEXTURE0);
	tex->bind();
}

void game_object::set_texture(texture *tex) {
	this->tex = tex;
	size.set_x((float)get_texture()->get_width());
	size.set_y((float)get_texture()->get_height());
}

void game_object::set_origin(float x, float y) {
	origin.set_x(x);
	origin.set_y(y);
}

void game_object::set_origin(const vector2f &position) {
	origin = position;
}

void game_object::set_center(const vector2f &position) {
	center = position;
}

bool game_object::on_intersect() {
	set_to_remove(true);
	return false;
}

void game_object::calculate_origin() {
	vector2f pos = get_origin();
	set_center(pos);
	float x = pos.get_x() - get_size().get_x() * 0.5f;
	float y = pos.get_y() - get_size().get_y() * 0.5f;
	set_origin(x, y);
}
