#ifndef APPLICATION_H
#define APPLICATION_H

#include <memory>

#include "controller.h"
#include "render_module.h"
#include "timer.h"
#include "game_object.h"
#include "input_receiver.h"
#include "world_module.h"
#include "script_module.h"

class application {
public:
	application() : is_active(false) {}
	~application() {}

	void set_active(bool in_val) { is_active = in_val; }

	void start_up();
	void run();
	void shut_down();

	void print_video_info();
	void toggle_window_size();
	void toggle_wireframe();
	void show_current_time();

private:
	bool is_active;

	std::unique_ptr<render_module>	m_renderer;
	std::unique_ptr<world_module>	m_world;

	std::unique_ptr<timer>			m_timer;
	
	std::unique_ptr<controller>		m_controller;
	std::unique_ptr<input_receiver> m_receiver;

	std::unique_ptr<script_module>	m_scripts;
};
#endif // APPLICATION_H
