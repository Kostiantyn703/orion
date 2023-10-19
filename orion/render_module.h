#ifndef RENDER_MODULE_H
#define RENDER_MODULE_H

#include <memory>

#include "window.h"
#include "buffer_object.h"
#include "render_object.h"

class render_module {
using render_objects = std::vector<render_object*>;
public:
	render_module();
	~render_module();

	void init();
	void run();

	void add_object(render_object *in_obj) { m_a_objects.push_back(in_obj); }
	 
	void toggle_wireframe() { is_wireframe = !is_wireframe; }

	window *get_window() const { return m_window.get();	}

private:
	bool is_wireframe;

	std::unique_ptr<window>	m_window;
	render_objects m_a_objects;

};
#endif // RENDER_MODULE_H
