#include "game_state.h"
#include "application.h"
#include "render_module.h"

void start_state::process(application &in_game, float delta_time) {}

void start_state::on_transition(application &in_game) {}

void active_state::process(application &in_game, float delta_time) {
	in_game.update_world(delta_time);
}

void active_state::on_transition(application &in_game) {
	in_game.clear_objects();
	in_game.init_game();
}
