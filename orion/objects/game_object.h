#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "../utils/globals.h"

#include "../render/renderable.h"
#include "../input/controller.h"

#include "../interfaces/collidable.h"
#include "../interfaces/movable.h"

class game_object : public renderable, public collidable, public movable {
public:
	game_object(const vector2f &initial_point);
	virtual ~game_object() {}

	virtual void init() {}

	virtual void update(float delta_time);

	virtual void draw(const shader_program &shader) override;
	virtual void set_texture(texture *tex) override;


	void set_to_remove(bool val) { to_remove = val; }
	bool should_remove() const { return to_remove; }

	virtual bool on_intersect()	override;

	const vector2f &get_origin() const { return origin; }
	vector2f *get_origin_ptr() { return &origin; }
	const vector2f &get_size() const { return size; }
	const vector2f &get_center() const { return center; }

	void set_rotation(float rotation) { this->rotation = rotation; }
	float get_rotation() const { return rotation; }

	size_t get_score_value() const { return score; }

protected:
	void set_origin(float x, float y);
	void set_origin(const vector2f &position);
	void set_center(const vector2f &position);

	void calculate_origin();

	void set_score_value(size_t val) { score = val; }

private:
	bool to_remove;
	float rotation;

	size_t score;

	vector2f origin;
	vector2f size;
	vector2f center;
};
#endif // GAME_OBJECT_H