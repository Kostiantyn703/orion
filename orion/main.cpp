#include <memory>
#include "application.h"

int main(int argc, char* args[]) {
	std::unique_ptr<application> game = std::make_unique<application>();
	game->start_up();
	game->run();
	return 0;
}