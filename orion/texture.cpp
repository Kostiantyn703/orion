#include "texture.h"


texture::texture()
	: m_target (GL_TEXTURE_2D), m_format (GL_RGBA), m_width (0), m_height (0), m_channels (0)
{
	create();
}

texture::~texture() {}

void texture::bind() {
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(m_target, m_id);
}
void texture::unbind() {
	glBindTexture(m_target, 0);
}

void texture::init_data(unsigned char *data, const GLint &width, const GLint &height, const GLint &channels) {
	bind();

	glTexParameteri(m_target, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(m_target, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

	glTexParameteri(m_target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(m_target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(m_target, 0, m_format, width, height, 0, m_format, GL_UNSIGNED_BYTE, data);

	unbind();
}

void texture::create() {
	glGenTextures(1, &m_id);
}