#ifndef GLOBALS_H
#define GLOBALS_H

// window
constexpr float		WINDOW_HEIGHT	= 720.f;
constexpr float		WINDOW_WIDTH	= 1280.f;
static const char	*GAME_NAME	= "PROJECT ORION";

// values
constexpr float		BULLET_VELOCITY		= 650.f;
constexpr float		SPACESHIP_VELOCITY	= 500.f;
constexpr float		WEAPON_RELOAD_TIME	= 0.8f;

constexpr float		OUT_OFFSET		= 20.f;
constexpr float		SIZE_SCALAR		= 0.1f;

constexpr float		METEOR_MAX_SPAWN_TIME = 5.f;
constexpr int		METEOR_SPAWN_RANGE = 200;

constexpr size_t	METEOR_SCORE = 2;
constexpr size_t	SPACESHIP_SCORE = 5;

// difficulty
constexpr size_t	DIFFICULTY_STEP			= 20;
constexpr float		METEOR_VELOCITY			= 400.f;
constexpr float		METEOR_VELOCITY_STEP	= 20.f;
constexpr float		SHIP_SPAWN_TIME			= 5.f;
constexpr float		SHIP_MIN_SPAWN_TIME		= 1.f;
constexpr float		SHIP_SPAWN_TIME_STEP	= 0.3f;

// shaders
static const char	*SPRITE_ADDRESS_VERT	= "../content/shaders/sprite.vert";
static const char	*SPRITE_ADDRESS_FRAG	= "../content/shaders/sprite.frag";
static const char	*DEBUG_ADDRESS_VERT		= "../content/shaders/debug.vert";
static const char	*DEBUG_ADDRESS_FRAG		= "../content/shaders/debug.frag";
static const char	*TEXT_ADDRESS_VERT		= "../content/shaders/text.vert";
static const char	*TEXT_ADDRESS_FRAG		= "../content/shaders/text.frag";

static const char	*SPRITE_NAME		= "sprite";
static const char	*DEBUG_NAME			= "debug";
static const char	*TEXT_NAME			= "text";

// textures addresses
static const char	*TEX_ADDRESS_BACKGROUND			= "../content/images/background.png";
static const char	*TEX_ADDRESS_ENEMY_00			= "../content/images/enemy00.png";
static const char	*TEX_ADDRESS_ENEMY_01			= "../content/images/enemy01.png";
static const char	*TEX_ADDRESS_ENEMY_02			= "../content/images/enemy02.png";
static const char	*TEX_ADDRESS_SHIP				= "../content/images/ship.png";
static const char	*TEX_ADDRESS_METEOR_BROWN_BIG	= "../content/images/meteor_brown_big.png";
static const char	*TEX_ADDRESS_BULLET_GREEN		= "../content/images/bullet_green.png";
static const char	*TEX_ADDRESS_BULLET_RED			= "../content/images/bullet_red.png";

// textures names
static const char	*TEX_NAME_BACKGROUND		= "background";
static const char	*TEX_NAME_ENEMY_00			= "enemy00";
static const char	*TEX_NAME_ENEMY_01			= "enemy01";
static const char	*TEX_NAME_ENEMY_02			= "enemy02";
static const char	*TEX_NAME_SHIP				= "ship";
static const char	*TEX_NAME_METEOR_BROWN_BIG	= "meteor_brown_big";
static const char	*TEX_NAME_BULLET_GREEN		= "bullet_green";
static const char	*TEX_NAME_BULLET_RED		= "bullet_red";

// scripts
static const char	*SCRIPTS_PATH				= "../content/scripts/";

// fonts
static const char	*FONT_PATH					= "../content/fonts/kenvector_future.ttf";

// vertices
static float vertices[] = {
	0.f, 1.f,		0.f, 1.f,
	1.f, 0.f,		1.f, 0.f,
	0.f, 0.f,		0.f, 0.f,

	0.f, 1.f,		0.f, 1.f,
	1.f, 1.f,		1.f, 1.f,
	1.f, 0.f,		1.f, 0.f
};

// vector class
class vector2f {
public:
	vector2f() {}
	vector2f(float in_x, float in_y) : m_x(in_x), m_y(in_y) {}
	~vector2f() {}

	void	set_x(float in_x)	{	m_x = in_x;	}
	void	set_y(float in_y)	{	m_y = in_y;	}
	float	get_x()	const		{	return m_x;	}
	float	get_y()	const		{	return m_y;	}

	vector2f	get_inverse	()	const	{	return vector2f(m_x * -1, m_y * -1);	}
	vector2f	get_swapped	()	const	{	return vector2f(m_y, m_x);				}

	vector2f &operator=(const vector2f &rhs) {
		m_x = rhs.m_x;
		m_y = rhs.m_y;
		return *this;
	}

	friend vector2f operator*(vector2f lhs, float in_scalar) {
		lhs.m_x *= in_scalar;
		lhs.m_y *= in_scalar;
		return lhs;
	}

	friend vector2f operator+(vector2f lhs, const vector2f &rhs) {
		lhs.m_x += rhs.m_x;
		lhs.m_y += rhs.m_y;
		return lhs;
	}

	friend vector2f operator-(vector2f lhs, const vector2f &rhs) {
		lhs.m_x -= rhs.m_x;
		lhs.m_y -= rhs.m_y;
		return lhs;
	}
private:
	float m_x;
	float m_y;
};

enum class border_side {
	BS_NORTH = 0,
	BS_EAST,
	BS_SOUTH,
	BS_WEST,
	BS_NONE = -1
};

struct range {
	int m_min = 0;
	int m_max = 0;

	bool is_valid() const { return m_min != m_max; }
};
#endif // !GLOBALS_H
