#include "resource_module.h"

#include <iostream>
#include <fstream>
#include <sstream>

#include "SDL_log.h"
#include "globals.h"
#include "stb_image.h"
#include "shader.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"


resource_module::resource_module() {
	init_shaders();
	load_textures();
}

resource_module::~resource_module() {}

void resource_module::init_shaders() {
	std::string v_shader_source;
	if (!load_shader(VERT_SHADER_ADDRESS, v_shader_source)) {
		return;
	}
	std::string f_shader_source;
	if (!load_shader(FRAG_SHADER_ADDRESS, f_shader_source)) {
		return;
	}
	compile_shaders(v_shader_source, f_shader_source);
}

void resource_module::compile_shaders(const std::string &in_vertex_source, const std::string &in_fragment_source) {
	std::unique_ptr<shader> vert = std::make_unique<shader>(in_vertex_source.data(), GL_VERTEX_SHADER);
	vert->compile();

	std::unique_ptr<shader> frag = std::make_unique<shader>(in_fragment_source.data(), GL_FRAGMENT_SHADER);
	frag->compile();

	m_shaders.insert(std::make_pair(std::string(SPRITE_SHADER_NAME), std::make_unique<shader_program>()));
	m_shaders.at(SPRITE_SHADER_NAME)->attach_shader(vert->get_id());
	m_shaders.at(SPRITE_SHADER_NAME)->attach_shader(frag->get_id());
	m_shaders.at(SPRITE_SHADER_NAME)->link();
	m_shaders.at(SPRITE_SHADER_NAME)->use();

	glm::mat4 projection = glm::ortho(0.f, WINDOW_WIDTH, WINDOW_HEIGHT, 0.f, -1.f, 1.f);
	glUniformMatrix4fv(glGetUniformLocation(m_shaders.at(SPRITE_SHADER_NAME)->id(), "projection"), 1, false, glm::value_ptr(projection));

	vert->destroy();
	frag->destroy();
}

void resource_module::load_textures() {
	int width, height, nr_channels;
	unsigned char *texture_data = load_texture(width, height, nr_channels);

	m_textures.insert(std::make_pair(std::string(SHIP_TEXTURE_NAME), std::make_unique<texture>()));
	m_textures.at(SHIP_TEXTURE_NAME)->init_data(texture_data, width, height, nr_channels);
	
	free_texture_data(texture_data);
}

void resource_module::free_texture_data(unsigned char *in_data) {
	stbi_image_free(in_data);
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

unsigned char *resource_module::load_texture(int &out_width, int &out_height, int &out_channels) {
	//stbi_set_flip_vertically_on_load(true);
	return stbi_load(SHIP_TEXTURE_ADDRESS, &out_width, &out_height, &out_channels, 0);
}
