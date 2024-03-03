#include "application.h"

#include <SDL.h>
#include <SDL_timer.h>

#include "render/renderable.h"
#include "gameplay/game_state.h"

void application::start_up() {
	m_renderer	= std::make_unique<render_module>();

	m_controller	= std::make_unique<controller>();
	m_receiver		= std::make_unique<input_receiver>();

	m_world = std::make_unique<world_module>();

	m_scripts = std::make_unique<script_module>();
	m_scripts->collect_scripts(SCRIPTS_PATH, m_world->m_block_data);
	m_world->init();

	m_renderer->init();

	m_states.push_back(std::make_unique<start_state>());
	m_states.push_back(std::make_unique<active_state>());
	m_cur_state_idx = 0;

	is_active = true;
}

void application::init_game() {
	m_world->init_player(m_controller.get());
	is_game_started = true;
}

void application::clear_objects() {
	m_world->clear_objects();
}

void application::run() {
	Uint64 last_time = 0;
	while (is_active) {
		Uint64 cur_time = SDL_GetTicks64();
		float delta_time = (cur_time - last_time) / 1000.f;
		last_time = cur_time;

		handle_input();
		m_states[m_cur_state_idx]->process(*this, delta_time);

		render();
	}
}

void application::shut_down() {}

void application::render() {
	m_renderer->run(m_world.get());
}

void application::handle_input() {
	m_controller->handle_input(m_receiver.get());

	if (m_receiver->esc_pressed) {
		is_active = false;
	}
	if (!is_game_started && m_receiver->enter_pressed && m_cur_state_idx == 0) {
		change_state();
	}
}

void application::update_world(float delta_time) {
	m_world->update(delta_time);
	m_renderer->scroll_background(delta_time);
	if (m_cur_state_idx > 0 && m_world->get_game_over()) {
		change_state();
	}
}

void application::change_state() {
	m_states[m_cur_state_idx]->on_transition(*this);
	if (m_cur_state_idx == 0) {
		++m_cur_state_idx;
	} else {
		--m_cur_state_idx;
	}
}
