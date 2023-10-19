#ifndef GLOBALS_H
#define GLOBALS_H

constexpr int		WINDOW_HEIGHT	= 600;
constexpr int		WINDOW_WIDTH	= 800;
static const char	*WINDOW_NAME	= "PROJECT ORION";

static const char	*vert_shader_address = "../content/shaders/vertex.vert";
static const char	*frag_shader_address = "../content/shaders/fragment.frag";

static const char	*ship_texture_address = "../content/images/ship.png";

static float vertices[] = {
	0.2f,	0.2f,	1.f,	1.f,
	0.2f,	-0.2f,	1.f,	0.f,
	-0.2f,	-0.2f,	0.f,	0.f,
	-0.2f,	0.2f,	0.f,	1.f
};

static unsigned int indices[] = {
	0, 1, 2,
	0, 2, 3
};

#endif // !GLOBALS_H

