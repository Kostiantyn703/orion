#ifndef WINDOW_H
#define WINDOW_H

struct SDL_Window;

class window {
public:
	window();
	~window();

private:
	unsigned int m_flags;

	SDL_Window *m_window;

};
#endif WINDOW_H
