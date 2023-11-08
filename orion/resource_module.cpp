#include "resource_module.h"

#include "SDL_log.h"
#include "globals.h"
#include "stb_image.h"

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
	create_texture(TEX_ADDRESS_SHIP,				TEX_NAME_SHIP				);
	create_texture(TEX_ADDRESS_ENEMY,				TEX_NAME_ENEMY				);
	create_texture(TEX_ADDRESS_METEOR_BROWN_BIG,	TEX_NAME_METEOR_BROWN_BIG	);
	create_texture(TEX_ADDRESS_METEOR_BROWN_MED,	TEX_NAME_METEOR_BROWN_MED	);
	create_texture(TEX_ADDRESS_BULLET,				TEX_NAME_BULLET				);
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
