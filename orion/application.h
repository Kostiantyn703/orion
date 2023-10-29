#ifndef APPLICATION_H
#define APPLICATION_H

#include <memory>

#include "controller.h"
#include "render_module.h"
#include "timer.h"
#include "game_object.h"
#include "resource_module.h"

using objects = std::vector<game_object*>;

class object_storage {
public:
	object_storage() {}
	~object_storage() {}

	void update(float delta_time);
	void create_object(float in_x, float in_y);

	objects m_objects;
};

class application {
public:
	application();
	~application();

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

	std::unique_ptr<resource_module> m_resources;
	std::unique_ptr<render_module>	m_renderer;
	std::unique_ptr<controller>		m_input_handler;
	std::unique_ptr<timer>			m_timer;

	object_storage					m_storage;
};
#endif // APPLICATION_H