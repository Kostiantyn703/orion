#ifndef RENDER_MODULE_H
#define RENDER_MODULE_H

#include <memory>

#include "window.h"
#include "shader_program.h"
#include "vertex_array.h"

class render_module {
public:
	render_module();
	~render_module();

	void init();
	void run();	// update() draw() ???

private:
	std::unique_ptr<window> m_window;
	std::unique_ptr<shader_program> m_shader_program;
	std::unique_ptr<vertex_array> m_vertex_array;
};
#endif // RENDER_MODULE_H
