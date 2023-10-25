#ifndef RENDER_MODULE_H
#define RENDER_MODULE_H

#include <memory>

#include "window.h"
#include "buffer_object.h"
#include "renderable.h"
#include "resource_module.h"

class render_module {
using renderables = std::vector<renderable*>;
public:
	render_module();
	~render_module();

	void init();
	void run();

	void add_object(renderable &in_obj, resource_module &in_resources);
	 
	void toggle_wireframe() { is_wireframe = !is_wireframe; }

	window *get_window() const { return m_window.get();	}

private:
	bool is_wireframe;

	std::unique_ptr<window>	m_window;
	renderables m_objects;

};
#endif // RENDER_MODULE_H
