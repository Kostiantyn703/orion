#ifndef GLOBALS_H
#define GLOBALS_H
// window
constexpr float		WINDOW_HEIGHT	= 600.f;
constexpr float		WINDOW_WIDTH	= 800.f;
static const char	*WINDOW_NAME	= "PROJECT ORION";

// objects
constexpr float		BULLET_VELOCITY	= 2000.f;
constexpr float		PLAYER_VELOCITY	= 1000.f;

// shaders
static const char	*SPRITE_ADDRESS_VERT	= "../content/shaders/sprite.vert";
static const char	*SPRITE_ADDRESS_FRAG	= "../content/shaders/sprite.frag";
static const char	*DEBUG_ADDRESS_VERT		= "../content/shaders/debug.vert";
static const char	*DEBUG_ADDRESS_FRAG		= "../content/shaders/debug.frag";

static const char	*SPRITE_NAME		= "sprite";
static const char	*DEBUG_NAME			= "debug";

// textures
static const char	*TEX_ADDRESS_ENEMY				= "../content/images/enemy.png";
static const char	*TEX_ADDRESS_SHIP				= "../content/images/ship.png";
static const char	*TEX_ADDRESS_METEOR_BROWN_BIG	= "../content/images/meteor_brown_big.png";
static const char	*TEX_ADDRESS_METEOR_BROWN_MED	= "../content/images/meteor_brown_med.png";
static const char	*TEX_ADDRESS_BULLET				= "../content/images/bullet.png";

static const char	*TEX_NAME_ENEMY				= "enemy";
static const char	*TEX_NAME_SHIP				= "ship";
static const char	*TEX_NAME_METEOR_BROWN_BIG	= "meteor_brown_big";
static const char	*TEX_NAME_METEOR_BROWN_MED	= "meteor_brown_med";
static const char	*TEX_NAME_BULLET			= "bullet";

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
	point &operator=(const point &rhs) {
		x_pos = rhs.x_pos;
		y_pos = rhs.y_pos;
		return *this;
	}

	~point() {}
	
	float x_pos;
	float y_pos;
};
#endif // !GLOBALS_H
