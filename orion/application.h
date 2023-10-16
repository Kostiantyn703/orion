#ifndef APPLICATION_H
#define APPLICATION_H

#include <memory>

#include "controller.h"
#include "render_module.h"
#include "timer.h"

class application {
public:
	application();
	~application();

	void start_up();
	void run();
	void shut_down();

	void set_active(bool in_val) {	is_active = in_val;	}
	void print_video_info();
	void toggle_window_size();
	void toggle_wireframe();
	void show_current_time();

private:
	bool is_active;

	std::unique_ptr<render_module>	m_renderer;
	std::unique_ptr<controller>		m_input_handler;
	std::unique_ptr<timer>			m_timer;

};

#endif // APPLICATION_H
