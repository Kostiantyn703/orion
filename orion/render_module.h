#ifndef RENDER_MODULE_H
#define RENDER_MODULE_H

#include <memory>

#include "window.h"
#include "buffer_object.h"
#include "resource_module.h"
#include "vertex_array.h"
#include "renderable.h"

class render_module {
using renderables = std::vector<renderable*>;
public:
	render_module();
	~render_module();

	void init();
	void run(resource_module &in_resources);

	void add_object(renderable *in_obj);
	 
	void toggle_wireframe() { is_wireframe = !is_wireframe; }

	window *get_window() const { return m_window.get();	}

private:
	bool is_wireframe;

	std::unique_ptr<window>	m_window;

	std::unique_ptr<vertex_array>	m_vertex_array;
	std::unique_ptr<buffer_object>	m_vertex_buffer;

	renderables m_renderables;

};
#endif // RENDER_MODULE_H
