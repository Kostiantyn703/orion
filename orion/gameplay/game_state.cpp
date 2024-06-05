#include "game_state.h"

#include "../application.h"

void start_state::process(application &game, float delta_time) {}

void start_state::on_transition(application &game) {
	world_module &world = game.get_world();
	world.reset_score();
	world.reset_difficulty();
	world.set_show_title(false);
	world.set_show_score(false);
	game.init();
}

void active_state::process(application &game, float delta_time) {
	game.update_world(delta_time);
}

void active_state::on_transition(application &game) {
	world_module &world = game.get_world();
	world.set_game_over(false);
	world.set_show_score(true);
	game.reset();
}
