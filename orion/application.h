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

class game_state;

class application {
public:
	application() : is_active(false), m_curr_state(nullptr) {}
	~application() {}

	void set_active(bool in_val) { is_active = in_val; }

	void start_up();
	void run();
	void shut_down();

	void init_game();
	void clear_objects();

	void render();
	void handle_input();
	void update_world(float delta_time);

	void change_state();

private:
	bool is_active;

	game_state *m_curr_state;

	std::unique_ptr<script_module>	m_scripts;
	std::unique_ptr<render_module>	m_renderer;
	std::unique_ptr<world_module>	m_world;

	std::unique_ptr<timer>			m_timer;
	
	std::unique_ptr<controller>		m_controller;
	std::unique_ptr<input_receiver> m_receiver;
};
#endif // APPLICATION_H
