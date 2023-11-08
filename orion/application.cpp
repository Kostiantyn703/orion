#include "application.h"

#include "SDL.h"
#include "globals.h"
#include "renderable.h"

application::application() : is_active(false) {}

void application::start_up() {
	m_renderer	= std::make_unique<render_module>();
	m_resources	= std::make_unique<resource_module>();

	m_controller	= std::make_unique<controller>();
	m_receiver		= std::make_unique<input_receiver>();

	m_world = std::make_unique<world_module>();
	m_world->init_player(m_controller.get(), *m_resources.get());
	m_world->init_objects(*m_resources.get());
	
	m_renderer->init();

	for (auto it = m_world->m_objects.begin(); it != m_world->m_objects.end(); ++it) {
		m_renderer->add_object(*it);
	}

	m_timer = std::make_unique<timer>();
	m_timer->start();

	is_active = true;
}

void application::run() {
	float last_frame = m_timer->get_current_time();
	float curr_frame = 0.f;
	float delta_time = 0.f;
	while (is_active) {
		curr_frame = m_timer->get_current_time();
		delta_time = curr_frame - last_frame;
		delta_time *= 50.f;
		
		m_controller->handle_input(m_receiver.get());
		m_world->update(delta_time);
		m_renderer->run();

		last_frame = m_timer->get_current_time();
	}
}

void application::shut_down() {
	m_timer->stop();
}

void application::print_video_info() {
	SDL_Log("\t\t\t==== ==== ==== ==== ==== ====\n");
	int drivers_num = SDL_GetNumVideoDrivers();
	SDL_Log("Num of drivers is %d", drivers_num);

	for (int i = 0; i < drivers_num; ++i) {
		SDL_Log("Driver %d [%s]", i, SDL_GetVideoDriver(i));
	}
	SDL_Log("Current driver [%s]", SDL_GetCurrentVideoDriver());

	int num_displays = SDL_GetNumVideoDisplays();
	SDL_Log("Displays quantity [%d]", num_displays);
	for (int i = 0; i < num_displays; ++i) {
		SDL_Log("Display %d [%s]", i, SDL_GetDisplayName(i));

		SDL_Rect bounds;
		SDL_GetDisplayBounds(i, &bounds);
		SDL_Log("Bounds\n\tx [%d]\ty [%d]\th [%d]\tw [%d]", bounds.x, bounds.y, bounds.h, bounds.w);

		SDL_Rect ubounds;
		SDL_GetDisplayUsableBounds(i, &ubounds);
		SDL_Log("Usable Bounds\n\tx [%d]\ty [%d]\th [%d]\tw [%d]", ubounds.x, ubounds.y, ubounds.h, ubounds.w);

		// enum
		SDL_DisplayOrientation display_orient = SDL_GetDisplayOrientation(i);

		SDL_DisplayMode mode;
		//SDL_GetCurrentDisplayMode(i, &mode);
		//SDL_Log("Current Mode Info: format[%d] w [%d] h [%d] refresh_rate [%d]", mode.format, mode.w, mode.h, mode.refresh_rate);

		SDL_GetDesktopDisplayMode(i, &mode);
		SDL_Log("Current Mode Info: format[%d] w [%d] h [%d] refresh_rate [%d]", mode.format, mode.w, mode.h, mode.refresh_rate);
	}
	SDL_Log("\t\t\t==== ==== ==== ==== ==== ====\n");
}

void application::toggle_window_size() {
	m_renderer->get_window()->toggle_fullscreen();
}

void application::toggle_wireframe() {
	m_renderer->toggle_wireframe();
}

void application::show_current_time() {
	m_timer->current_clock();
}
