#ifndef RENDER_MODULE_H
#define RENDER_MODULE_H

#include <memory>
#include "window.h"
#include "shader.h"

class render_module {
public:
	render_module();
	~render_module();

	void init();
	void run();	// update() draw() ???
private:
	std::unique_ptr<window> m_window;
	std::unique_ptr<shader> m_shader;

};
#endif // RENDER_MODULE_H
