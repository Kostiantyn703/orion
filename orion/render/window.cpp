#include "window.h"

#include <SDL_video.h>
#include <SDL_log.h>
#include <SDL.h>

#include "glad/glad.h"

#include "../utils/globals.h"

#define log_error	if (SDL_GetError()[0]) {SDL_LogError(0, SDL_GetError()); }

game_window::game_window() {
	unsigned int flags = SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL;
	window = SDL_CreateWindow(GAME_NAME, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED
								,(int)WINDOW_WIDTH, (int)WINDOW_HEIGHT, flags);

	context = SDL_GL_CreateContext(window);
	gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_PROGRAM_POINT_SIZE);

	log_error;
}

game_window::~game_window() {
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
	log_error;
}

void game_window::swap() {
	SDL_GL_SwapWindow(window);
}
