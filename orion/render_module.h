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
#include "world_module.h"

class background : public renderable {
public:
	background() {}
	
	void init();

	virtual void draw(const shader_program &in_shader) override;
	virtual void set_texture(texture *in_texture) override {}

	vector2f m_size;
	float m_scroll_offset = 0.f;
};

struct character {
	size_t m_id;
	glm::ivec2 m_size;
	glm::ivec2 m_bearing;
	size_t m_advance;
};

class text_render_module {
	using char_map = std::map<char, character>;
public:
	text_render_module();
	~text_render_module();

	void init();

	void draw();

	void load();

private:
	std::unique_ptr<shader> m_shader;

	std::unique_ptr<vertex_array>	m_vertex_array;
	std::unique_ptr<buffer_object>	m_vertex_buffer;

	char_map m_characters;
};

class render_module {
	using shader_vec = std::vector<std::unique_ptr<shader_program>>;
public:
	render_module();
	~render_module() {}

	void init();

	void init_shader(const char *in_vert_address, const char *in_frag_address);
	void compile_shaders(const std::string &in_vertex_source, const std::string &in_fragment_source);
	bool load_shader(const char *source_address, std::string &out_shader_source);

	void run(world_module *in_world);
	void scroll_background(float delta_time);

	window *get_window() const { return m_window.get();	}

	background m_background;
private:
	std::unique_ptr<window>	m_window;

	std::unique_ptr<vertex_array>	m_vertex_array;
	std::unique_ptr<buffer_object>	m_vertex_buffer;

	shader_vec m_shaders;
};
#endif // RENDER_MODULE_H
