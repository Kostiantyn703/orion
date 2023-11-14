#ifndef GLOBALS_H
#define GLOBALS_H
// window
constexpr float		WINDOW_HEIGHT	= 600.f;
constexpr float		WINDOW_WIDTH	= 800.f;
static const char	*WINDOW_NAME	= "PROJECT ORION";

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
class vector2f {
public:
	vector2f() {}
	vector2f(float in_x, float in_y) : m_x(in_x), m_y(in_y) {}
	~vector2f() {}

	void	set_x(float in_x)	{	m_x = in_x;	}
	void	set_y(float in_y)	{	m_y = in_y;	}
	float	get_x()				{	return m_x;	}
	float	get_y()				{	return m_y;	}


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

class aabb {
public:
	aabb() : m_origin(0.f, 0.f), m_size(0.f, 0.f) {}
	~aabb() {}

	void		set_origin	(const vector2f &in_origin)	{	m_origin = in_origin;	}
	vector2f	get_origin	()	const					{	return m_origin;		}
	void		set_size	(const vector2f &in_size)	{	m_size = in_size;		}
	vector2f	get_size	()	const					{	return m_size;			}
	// TDOD: this works only for big objects, bullets should have aabb of the full texture size
	void calculate(vector2f &in_origin, vector2f &in_size) {
		vector2f aabb_origin = in_origin + (in_size * 0.2f);
		set_origin(aabb_origin);
		vector2f aabb_size = in_size * 0.6f;
		set_size(aabb_size);
	}

private:
	vector2f	m_origin;
	vector2f	m_size;
};
#endif // !GLOBALS_H
