#include "application.h"

#include <chrono>

#include <SDL.h>

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

// TODO: probably not the best decision, but ok for now
constexpr int FRAMES_PER_SECOND = 60;
constexpr std::chrono::milliseconds MS_PER_FRAME = std::chrono::milliseconds(1000 / FRAMES_PER_SECOND);
constexpr float DT_DISSIPATOR = 0.001f;
std::chrono::milliseconds FRAME_DELAY = std::chrono::milliseconds(0);
constexpr std::chrono::milliseconds FRAME_DELAY_TIME = std::chrono::milliseconds(1200);

void application::run() {
	while (is_active) {
		FRAME_DELAY -= MS_PER_FRAME;
		if (FRAME_DELAY > std::chrono::milliseconds(0))	continue;
		else if (FRAME_DELAY < std::chrono::milliseconds(0)) {
			FRAME_DELAY = FRAME_DELAY_TIME;
		}
		handle_input();
		float delta_time = MS_PER_FRAME.count() * DT_DISSIPATOR;
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
