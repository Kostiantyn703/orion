#ifndef RENDER_MODULE_H
#define RENDER_MODULE_H

#include <memory>
#include <string>
#include <vector>
#include <map>

#include "glad/glad.h"
#include "glm/glm.hpp"

#include "window.h"
#include "buffer_object.h"
#include "vertex_array.h"
#include "renderable.h"
#include "shader_program.h"

#include "../modules/world_module.h"

class background_renderer : public renderable {
public:
	background_renderer();
	virtual ~background_renderer() = default;

	void init();
	void scroll(float delta_time);

	virtual void set_texture(texture *tex) override;
	virtual void draw(const shader_program &shader) override;

	float scroll_offset;
	vector2f size;
};

struct character {
	unsigned int id;
	glm::ivec2 size;
	glm::ivec2 bearing;
	unsigned int advance;
};

class text_render_module {
	using char_map = std::map<char, character>;
public:
	text_render_module();

	void init();
	void load();

	void draw_title();
	void draw_score(const int score);

private:
	float left_offset;

	std::unique_ptr<shader_program> shader_prog;

	unsigned int vert_array;
	unsigned int vert_buffer;

	char_map characters;

	unsigned int font_size;

	glm::vec3 text_color;

	void draw(const std::string &text, float x, float y, float scale);
};

class render_module {
	using shader_vec = std::vector<std::unique_ptr<shader_program>>;
public:
	render_module();

	void init();

	void init_shader(const char *vert_address, const char *frag_address);
	void compile_shaders(const std::string &vertex_source, const std::string &fragment_source);

	void run(world_module *world);
	void scroll_background(float delta_time);

	game_window *get_window() const { return window.get();	}

	background_renderer background;
private:
	std::unique_ptr<game_window> window;

	std::unique_ptr<vertex_array> vert_array;
	std::unique_ptr<buffer_object> vert_buffer;

	std::unique_ptr<text_render_module> text_renderer;

	shader_vec shaders;
};
#endif // RENDER_MODULE_H
