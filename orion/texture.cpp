#include "texture.h"


texture::texture()
	: m_target (GL_TEXTURE_2D), m_format (GL_RGBA) , m_width (0), m_height (0), m_channels (0)
{
}

texture::texture(texture &in_texture) {
	m_id		= in_texture.m_id;
	m_target	= in_texture.m_target;
	m_format	= in_texture.m_format;
	m_width	= in_texture.m_width;
	m_height	= in_texture.m_height;
	m_channels	= in_texture.m_channels;
}

texture &texture::operator=(const texture &in_texture) {
	m_id = in_texture.m_id;
	m_target = in_texture.m_target;
	m_format = in_texture.m_format;
	m_width = in_texture.m_width;
	m_height = in_texture.m_height;
	m_channels = in_texture.m_channels;
	return *this;
}


void texture::bind() {
	glBindTexture(m_target, m_id);
}
void texture::unbind() {
	glBindTexture(m_target, 0);
}

void texture::init_data(unsigned char *data, const int &in_width, const int &in_height, const int &in_channels) {
	m_width		= in_width;
	m_height	= in_height;
	m_channels	= in_channels;
	
	create();

//	glActiveTexture(GL_TEXTURE0);
	bind();

	glTexParameteri(m_target, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(m_target, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexParameteri(m_target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(m_target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(m_target, 0, m_format, m_width, m_height, 0, m_format, GL_UNSIGNED_BYTE, data);

	unbind();
}

void texture::create() {
	glGenTextures(1, &m_id);
}