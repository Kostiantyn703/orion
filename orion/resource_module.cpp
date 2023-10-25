#include "resource_module.h"

#include <iostream>
#include <fstream>
#include <sstream>

#include "SDL_log.h"
#include "globals.h"
#include "stb_image.h"


bool shader_loader::load_shader(const char *source_address, std::string &out_shader_source) {
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

resource_module::resource_module() {
	m_shader_loader = std::make_unique<shader_loader>();
	init_shaders();
	load_textures();
}

resource_module::~resource_module() {}

void resource_module::init_shaders() {
	std::string v_shader_name("vert");
	std::string v_shader_source;
	if (!m_shader_loader->load_shader(vert_shader_address, v_shader_source)) {
		return;
	}
	std::pair<std::string, std::string> vert_shader (v_shader_name, v_shader_source);
	m_shader_sources.insert(vert_shader);

	std::string f_shader_name("frag");
	std::string f_shader_source;
	if (!m_shader_loader->load_shader(frag_shader_address, f_shader_source)) {
		return;
	}
	std::pair<std::string, std::string> frag_shader(f_shader_name, f_shader_source);
	m_shader_sources.insert(frag_shader);
}

void resource_module::load_textures() {
	int width, height, nr_channels;
	unsigned char *texture_data = load_texture(width, height, nr_channels);

	m_textures.insert(std::make_pair(std::string("ship"), std::make_unique<texture>()));
	m_textures.at("ship")->init_data(texture_data, width, height, nr_channels);
	
	free_texture_data(texture_data);
}

bool resource_module::get_shader_source(const std::string &in_key, std::string &out_value) {
	shader_map::iterator it = m_shader_sources.find(in_key);
	if (it != m_shader_sources.end()) {
		out_value = it->second;
	}
	if (out_value.empty()) {
		return false;
	}
	return true;
}

unsigned char *resource_module::load_texture(int &out_width, int &out_height, int &out_channels) {
	//stbi_set_flip_vertically_on_load(true);
	return stbi_load(ship_texture_address, &out_width, &out_height, &out_channels, 0);
}

void resource_module::free_texture_data(unsigned char *in_data) {
	stbi_image_free(in_data);
}
