#ifndef GLOBALS_H
#define GLOBALS_H

constexpr float		WINDOW_HEIGHT	= 600.f;
constexpr float		WINDOW_WIDTH	= 800.f;
static const char	*WINDOW_NAME	= "PROJECT ORION";

// shaders
static const char	*SHADER_ADDRESS_VERT	= "../content/shaders/vertex.vert";
static const char	*SHADER_ADDRESS_FRAG	= "../content/shaders/fragment.frag";

static const char	*SHADER_NAME_SPRITE		= "sprite";

// textures
static const char	*TEX_ADDRESS_SHIP				= "../content/images/ship.png";
static const char	*TEX_ADDRESS_METEOR_BROWN_BIG	= "../content/images/meteor_brown_big.png";
static const char	*TEX_ADDRESS_METEOR_BROWN_MED	= "../content/images/meteor_brown_med.png";

static const char	*TEX_NAME_SHIP				= "ship";
static const char	*TEX_NAME_METEOR_BROWN_BIG	= "meteor_brown_big";
static const char	*TEX_NAME_METEOR_BROWN_MED	= "meteor_brown_med";

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
