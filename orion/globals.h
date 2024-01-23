#ifndef GLOBALS_H
#define GLOBALS_H

// window
constexpr float		WINDOW_HEIGHT	= 1200.f * 0.6f;	// 600.f
constexpr float		WINDOW_WIDTH	= 1600.f * 0.75f;	// 800.f
static const char	*WINDOW_NAME	= "PROJECT ORION";

constexpr float		VELOCITY_COEFICIENT = 2.f;
// values
constexpr float		BULLET_VELOCITY	= 20.f * VELOCITY_COEFICIENT;
constexpr float		PLAYER_VELOCITY	= 10.f * VELOCITY_COEFICIENT;
constexpr float		METEOR_VELOCITY	= 2.f * VELOCITY_COEFICIENT;
constexpr float		MAX_RELOAD_TIME	= 15.f / VELOCITY_COEFICIENT;

constexpr float		REMOVE_OFFSET	= 15.f;

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

constexpr float		SIZE_SCALAR = 0.1f;

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

// direction data
constexpr size_t FV_IDX = 0; // forward vector index
constexpr size_t ROT_IDX = 1; // rotation index

static const char *DIR_UP_STR = "dir_up";
static const char *DIR_RIGHT_STR = "dir_right";
static const char *DIR_DOWN_STR = "dir_down";
static const char *DIR_LEFT_STR = "dir_left";

#include <map>
#include <string>

using dir_pair = std::pair<std::string, vector2f>;
using dir_map = std::map<std::string, vector2f>;

static dir_map g_dir_map;

static void init_dir_map(dir_map &in_map) {
	dir_pair up		= std::make_pair<std::string, vector2f>(DIR_UP_STR, vector2f(0.f, -1.f));
	dir_pair right	= std::make_pair<std::string, vector2f>(DIR_RIGHT_STR, vector2f(1.f, 0.f));
	dir_pair down	= std::make_pair<std::string, vector2f>(DIR_DOWN_STR, vector2f(0.f, 1.f));
	dir_pair left	= std::make_pair<std::string, vector2f>(DIR_LEFT_STR, vector2f(-1.f, 0.f));

	in_map.insert(up);
	in_map.insert(right);
	in_map.insert(down);
	in_map.insert(left);
}

using rot_pair = std::pair<std::string, float>;
using rot_map = std::map<std::string, float>;

static rot_map g_rot_map;

static void init_rot_map(rot_map &in_map) {
	rot_pair up		= std::make_pair<std::string, float>(DIR_UP_STR, 180.f);
	rot_pair right	= std::make_pair<std::string, float>(DIR_RIGHT_STR, 90.f);
	rot_pair down	= std::make_pair<std::string, float>(DIR_RIGHT_STR, 0.f);
	rot_pair left	= std::make_pair<std::string, float>(DIR_RIGHT_STR, 270);

	in_map.insert(up);
	in_map.insert(right);
	in_map.insert(down);
	in_map.insert(left);

}


#endif // !GLOBALS_H
