#ifndef GLOBALS_H
#define GLOBALS_H

constexpr float		WINDOW_HEIGHT	= 600.f;
constexpr float		WINDOW_WIDTH	= 800.f;
static const char	*WINDOW_NAME	= "PROJECT ORION";

// shaders
static const char	*VERT_SHADER_ADDRESS = "../content/shaders/vertex.vert";
static const char	*FRAG_SHADER_ADDRESS = "../content/shaders/fragment.frag";

static const char	*SPRITE_SHADER_NAME = "sprite";

// textures
static const char	*SHIP_TEX_ADDRESS				= "../content/images/ship.png";
static const char	*METEOR_BROWN_BIG_TEX_ADDRESS	= "../content/images/meteor_brown_big.png";
static const char	*METEOR_BROWN_MED_TEX_ADDRESS	= "../content/images/meteor_brown_med.png";

static const char	*SHIP_TEX_NAME	= "ship";
static const char	*METEOR_BROWN_BIG_TEX_NAME	= "meteor_brown_big";
static const char	*METEOR_BROWN_MED_TEX_NAME	= "meteor_brown_med";

// vertices
static float vertices[] = {
	0.f, 1.f,		0.f, 1.f,
	1.f, 0.f,		1.f, 0.f,
	0.f, 0.f,		0.f, 0.f,

	0.f, 1.f,		0.f, 1.f,
	1.f, 1.f,		1.f, 1.f,
	1.f, 0.f,		1.f, 0.f
};

// point class
class point {
public:
	point() {}
	point(float in_x, float in_y) : x_pos(in_x), y_pos(in_y) {}
	
	~point() {}
	
	float x_pos;
	float y_pos;
};
#endif // !GLOBALS_H
