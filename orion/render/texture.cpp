#include "texture.h"

#include "glad/glad.h"

texture::texture() : target(GL_TEXTURE_2D), width (0), height (0), channels (0) {}

texture::texture(texture &tex) {
	id = tex.id;
	target = tex.target;
	format = tex.format;
	width = tex.width;
	height = tex.height;
	channels = tex.channels;
}

texture &texture::operator=(const texture &tex) {
	id = tex.id;
	target = tex.target;
	format = tex.format;
	width = tex.width;
	height = tex.height;
	channels = tex.channels;
	return *this;
}

void texture::bind() {
	glBindTexture(target, id);
}

void texture::unbind() {
	glBindTexture(target, 0);
}

void texture::init_data(unsigned char *data, const int &width, const int &height, const int &channels) {
	this->width = width;
	this->height = height;
	this->channels = channels;
	this->format = (channels == 3) ? GL_RGB : GL_RGBA;
	
	create();
	bind();

	glTexParameteri(target, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(target, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(target, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);

	unbind();
}

void texture::create() {
	glGenTextures(1, &id);
}
