#ifndef GLOBALS_H
#define GLOBALS_H

constexpr float		WINDOW_HEIGHT	= 600.f;
constexpr float		WINDOW_WIDTH	= 800.f;
static const char	*WINDOW_NAME	= "PROJECT ORION";

static const char	*VERT_SHADER_ADDRESS = "../content/shaders/vertex.vert";
static const char	*FRAG_SHADER_ADDRESS = "../content/shaders/fragment.frag";

static const char	*SHIP_TEXTURE_ADDRESS = "../content/images/ship.png";

static const char	*SHIP_TEXTURE_NAME	= "ship";
static const char	*SPRITE_SHADER_NAME	= "sprite";


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

class point {
public:
	point() {}
	point(float in_x, float in_y) : x_pos(in_x), y_pos(in_y) {}
	
	~point() {}
	
	float x_pos;
	float y_pos;
};
#endif // !GLOBALS_H

