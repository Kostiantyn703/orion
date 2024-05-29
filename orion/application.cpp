#include "application.h"

#include <SDL.h>
#include <SDL_timer.h>

#include "render/renderable.h"
#include "gameplay/game_state.h"

application::application() : active(false), game_started(false), state_idx(0) {}

application::~application() {
	states.clear();
}

void application::init() {
	world->init_player(input_controller.get());
	game_started = true;
}

void application::start_up() {
	renderer = std::make_unique<render_module>();

	input_controller = std::make_unique<controller>();
	receiver = std::make_unique<input_receiver>();

	world = std::make_unique<world_module>();

	scripts = std::make_unique<script_module>();
	scripts->collect_scripts(SCRIPTS_PATH, world->m_block_data);
	world->init();

	renderer->init();

	states.push_back(std::make_unique<start_state>());
	states.push_back(std::make_unique<active_state>());

	active = true;
}

void application::run() {
	Uint64 last_time = 0;
	while (active) {
		Uint64 cur_time = SDL_GetTicks64();
		float delta_time = (cur_time - last_time) / 1000.f;
		last_time = cur_time;

		handle_input();
		states[state_idx]->process(*this, delta_time);

		render();
	}
}

void application::handle_input() {
	input_controller->handle_input(receiver.get());

	if (receiver->esc_pressed) {
		active = false;
	}
	if (start_game_condition()) {
		change_state();
	}
}

void application::render() {
	renderer->run(world.get());
}

void application::reset() {
	clear_objects();
	game_started = false;
}

void application::clear_objects() {
	world->clear_objects();
}

void application::update_world(float delta_time) {
	world->update(delta_time);
	renderer->scroll_background(delta_time);
	if (game_over_condition()) {
		change_state();
	}
}

void application::change_state() {
	states[state_idx]->on_transition(*this);
	if (state_idx == 0) {
		++state_idx;
	} else {
		--state_idx;
	}
}

bool application::start_game_condition() const {
	return !game_started && receiver->enter_pressed && state_idx == 0;
}

bool application::game_over_condition() const {
	return state_idx > 0 && world->get_game_over();
}
