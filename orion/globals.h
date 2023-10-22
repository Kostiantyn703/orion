#ifndef GLOBALS_H
#define GLOBALS_H

constexpr float		WINDOW_HEIGHT	= 600.f;
constexpr float		WINDOW_WIDTH	= 800.f;
static const char	*WINDOW_NAME	= "PROJECT ORION";

static const char	*vert_shader_address = "../content/shaders/vertex.vert";
static const char	*frag_shader_address = "../content/shaders/fragment.frag";

static const char	*ship_texture_address = "../content/images/ship.png";

//static float vertices[] = {
//	0.2f,	0.2f,	1.f,	1.f,
//	0.2f,	-0.2f,	1.f,	0.f,
//	-0.2f,	-0.2f,	0.f,	0.f,
//	-0.2f,	0.2f,	0.f,	1.f
//};

static float vertices[] = {
	1.f,	1.f,	1.f,	1.f,
	1.f,	-1.f,	1.f,	0.f,
	-1.f,	-1.f,	0.f,	0.f,
	-1.f,	1.f,	0.f,	1.f
};

static unsigned int indices[] = {
	0, 1, 2,
	0, 2, 3
};

struct point {
	float x_pos;
	float y_pos;
};

#endif // !GLOBALS_H

