#include "resource_module.h"

#include <iostream>
#include <fstream>
#include <sstream>

#include <SDL_log.h>

#include "../utils/globals.h"
#include "../utils/stb_image.h"

resource_module *resource_module::instance = nullptr;

resource_module::resource_module() {
	load_textures();
}

resource_module *resource_module::get_instance() {
	if (instance == nullptr) {
		instance = new resource_module();
	}
	return instance;
}

void resource_module::load_textures() {
	create_texture(TEX_ADDRESS_BACKGROUND,			TEX_NAME_BACKGROUND			);
	create_texture(TEX_ADDRESS_SHIP,				TEX_NAME_SHIP				);
	create_texture(TEX_ADDRESS_ENEMY_00,			TEX_NAME_ENEMY_00			);
	create_texture(TEX_ADDRESS_ENEMY_01,			TEX_NAME_ENEMY_01			);
	create_texture(TEX_ADDRESS_ENEMY_02,			TEX_NAME_ENEMY_02			);
	create_texture(TEX_ADDRESS_METEOR_BROWN_BIG,	TEX_NAME_METEOR_BROWN_BIG	);
	create_texture(TEX_ADDRESS_BULLET_GREEN,		TEX_NAME_BULLET_GREEN		);
	create_texture(TEX_ADDRESS_BULLET_RED,			TEX_NAME_BULLET_RED			);
}

bool resource_module::load_shader(const char *source_address, std::string &shader_source) {
	std::ifstream read_stream(source_address);
	if (!read_stream.is_open()) {
		SDL_LogError(0, "Shader source was failed to load from file.\nFile address [%s]", source_address);
		return false;
	}

	std::stringstream str_stream;
	str_stream << read_stream.rdbuf();
	shader_source = str_stream.str();
	if (shader_source.empty()) {
		SDL_LogError(0, "Shader source code was empty.");
		return false;
	}
	return true;
}

void resource_module::create_texture(const char *tex_address, const char *tex_name) {
	int width, height, nr_channels;
	unsigned char *texture_data = load_texture(tex_address, width, height, nr_channels);

	texture new_tex;
	new_tex.init_data(texture_data, width, height, nr_channels);

	textures.insert(std::make_pair(std::string(tex_name), std::make_unique<texture>(new_tex)));

	free_texture_data(texture_data);
}

unsigned char *resource_module::load_texture(const char *tex_address, int &width, int &height, int &channels) {
	return stbi_load(tex_address, &width, &height, &channels, 0);
}

void resource_module::free_texture_data(unsigned char *data) {
	stbi_image_free(data);
}
