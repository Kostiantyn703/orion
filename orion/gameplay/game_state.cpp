#include "game_state.h"

#include "../application.h"
#include "../render/render_module.h"

void start_state::process(application &in_game, float delta_time) {}

void start_state::on_transition(application &in_game) {
	world_module &world = in_game.get_world();
	world.reset_score();
	world.reset_difficulty();
	world.set_show_title(false);
	world.set_show_score(false);
	in_game.init_game();
}

void active_state::process(application &in_game, float delta_time) {
	in_game.update_world(delta_time);
}

void active_state::on_transition(application &in_game) {
	world_module &world = in_game.get_world();
	world.set_game_over(false);
	world.set_show_score(true);
	in_game.clear_objects();
	in_game.is_game_started = false;
}
