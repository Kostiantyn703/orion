#include "application.h"

#include "SDL.h"
#include "renderable.h"
#include <chrono>
#include "game_state.h"

void application::start_up() {
	m_renderer	= std::make_unique<render_module>();

	m_controller	= std::make_unique<controller>();
	m_receiver		= std::make_unique<input_receiver>();

	m_world = std::make_unique<world_module>();

	m_scripts = std::make_unique<script_module>();
	m_scripts->collect_scripts(SCRIPTS_PATH, m_world->m_block_data);
	m_world->init();

	m_renderer->init();

	m_timer = std::make_unique<timer>();
	m_timer->start();
	
	m_curr_state = new start_state();

	is_active = true;
}

void application::init_game() {
	m_world->init_player(m_controller.get());
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
		if (m_curr_state) {
			m_curr_state->process(*this, delta_time);
		}
		render();
	}
}

void application::shut_down() {
	m_timer->stop();
}

void application::render() {
	m_renderer->run(m_world.get());
}

void application::handle_input() {
	m_controller->handle_input(m_receiver.get());
	// TODO: quick check
	if (m_receiver->esc_pressed) {
		is_active = false;
	}
	if (m_receiver->enter_pressed) {
		change_state();
		m_receiver->enter_pressed = false;
	}
}

void application::update_world(float delta_time) {
	m_world->update(delta_time);
	m_renderer->scroll_background(delta_time);
}

void application::change_state() {
	delete m_curr_state;
	m_curr_state = new active_state();
	m_curr_state->on_transition(*this);
	m_world->show_title = false;
}
