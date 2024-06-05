#ifndef APPLICATION_H
#define APPLICATION_H

#include <memory>

#include "input/controller.h"
#include "input/input_receiver.h"

#include "modules/world_module.h"
#include "modules/script_module.h"

#include "render/render_module.h"
#include "objects/game_object.h"
#include "gameplay/game_state.h"

class application {
public:
	application();
	~application();

	void init();

	void start_up();
	void run();

	void handle_input();
	void render();

	void reset();
	void clear_objects();

	void update_world(float delta_time);

	void change_state();

	bool start_game_condition() const;
	bool game_over_condition() const;

	void start_game(bool val) { game_started = val; }
	bool is_game_started() const { return game_started; }

	void set_active(bool val) { active = val; }
	world_module &get_world() const { return *world.get(); }

private:
	bool active;
	bool game_started;
	size_t state_idx;

	std::vector<std::unique_ptr<game_state>> states;

	std::unique_ptr<script_module> scripts;
	std::unique_ptr<render_module> renderer;
	std::unique_ptr<world_module> world;

	std::unique_ptr<input_controller> controller;
	std::unique_ptr<input_receiver> receiver;
};
#endif // APPLICATION_H
