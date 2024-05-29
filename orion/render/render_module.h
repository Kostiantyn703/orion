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

	vector2f size;
	float scroll_offset;
	float scroll_speed;
};

struct character {
	unsigned int m_id;
	glm::ivec2 m_size;
	glm::ivec2 m_bearing;
	unsigned int m_advance;
};

class text_render_module {
	using char_map = std::map<char, character>;
public:
	text_render_module();

	void init();
	void load();

	void draw_title();
	void draw_score(const int in_score);

private:
	float m_left_offset;

	std::unique_ptr<shader_program> m_shader;

	unsigned int m_vertex_array;
	unsigned int m_vertex_buffer;

	char_map m_characters;

	unsigned int m_font_size;

	glm::vec3 m_text_color;

	void draw(const std::string &in_text, float in_x, float in_y, float in_scale);
};

class render_module {
	using shader_vec = std::vector<std::unique_ptr<shader_program>>;
public:
	render_module();
	~render_module() {}

	void init();

	void init_shader(const char *in_vert_address, const char *in_frag_address);
	void compile_shaders(const std::string &in_vertex_source, const std::string &in_fragment_source);

	void run(world_module *in_world);
	void scroll_background(float delta_time);

	window *get_window() const { return m_window.get();	}

	background_renderer background;
private:
	std::unique_ptr<window>	m_window;

	std::unique_ptr<vertex_array>	m_vertex_array;
	std::unique_ptr<buffer_object>	m_vertex_buffer;

	std::unique_ptr<text_render_module> m_text_renderer;

	shader_vec m_shaders;
};
#endif // RENDER_MODULE_H
