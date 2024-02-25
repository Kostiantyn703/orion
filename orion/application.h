#ifndef APPLICATION_H
#define APPLICATION_H

#include <memory>

#include "input/controller.h"
#include "input/input_receiver.h"

#include "render/render_module.h"
#include "modules/world_module.h"
#include "modules/script_module.h"

#include "objects/game_object.h"
#include "game_state.h"

class application {
public:
	application() : is_active(false) {}
	~application() { m_states.clear(); }

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

	world_module &get_world() const { return *m_world.get(); }

	bool is_game_started = false;

private:
	bool is_active;

	size_t m_cur_state_idx = 0;
	std::vector<std::unique_ptr<game_state>> m_states;

	std::unique_ptr<script_module>	m_scripts;
	std::unique_ptr<render_module>	m_renderer;
	std::unique_ptr<world_module>	m_world;

	std::unique_ptr<controller>		m_controller;
	std::unique_ptr<input_receiver> m_receiver;
};
#endif // APPLICATION_H
