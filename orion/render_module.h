#ifndef RENDER_MODULE_H
#define RENDER_MODULE_H

#include <memory>
#include <string>
#include <vector>

#include "window.h"
#include "buffer_object.h"
#include "vertex_array.h"
#include "renderable.h"
#include "shader_program.h"
#include "world_module.h"

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
	 
	void toggle_wireframe() { is_wireframe = !is_wireframe; }

	window *get_window() const { return m_window.get();	}

private:
	bool is_wireframe;

	std::unique_ptr<window>	m_window;

	std::unique_ptr<vertex_array>	m_vertex_array;
	std::unique_ptr<buffer_object>	m_vertex_buffer;

	shader_vec m_shaders;
};
#endif // RENDER_MODULE_H
