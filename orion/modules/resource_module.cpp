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

bool resource_module::load_shader(const char *source_address, std::string &out_shader_source) {
	std::ifstream read_stream(source_address);
	if (!read_stream.is_open()) {
		SDL_LogError(0, "Shader source was failed to load from file.\nFile address [%s]", source_address);
		return false;
	}

	std::stringstream str_stream;
	str_stream << read_stream.rdbuf();
	out_shader_source = str_stream.str();
	if (out_shader_source.empty()) {
		SDL_LogError(0, "Shader source code was empty.");
		return false;
	}
	return true;
}

void resource_module::create_texture(const char *in_tex_address, const char *in_tex_name) {
	int width, height, nr_channels;
	unsigned char *texture_data = load_texture(in_tex_address, width, height, nr_channels);

	texture new_tex;
	new_tex.init_data(texture_data, width, height, nr_channels);

	m_textures.insert(std::make_pair(std::string(in_tex_name), std::make_unique<texture>(new_tex)));

	free_texture_data(texture_data);
}

unsigned char *resource_module::load_texture(const char *in_tex_address, int &out_width, int &out_height, int &out_channels) {
	return stbi_load(in_tex_address, &out_width, &out_height, &out_channels, 0);
}

void resource_module::free_texture_data(unsigned char *in_data) {
	stbi_image_free(in_data);
}
