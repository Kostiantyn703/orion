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
	//init_shader(DEBUG_ADDRESS_VERT, DEBUG_ADDRESS_FRAG);
	init_shader(SPRITE_ADDRESS_VERT, SPRITE_ADDRESS_FRAG);
	load_textures();
}
void resource_module::init_shader(const char *in_vert_address, const char *in_frag_address) {
	std::string v_shader_source;
	if (!load_shader(in_vert_address, v_shader_source)) {
		return;
	}
	std::string f_shader_source;
	if (!load_shader(in_frag_address, f_shader_source)) {
		return;
	}
	compile_shaders(v_shader_source, f_shader_source);
}

void resource_module::compile_shaders(const std::string &in_vertex_source, const std::string &in_fragment_source) {
	std::unique_ptr<shader> vert = std::make_unique<shader>(in_vertex_source.data(), GL_VERTEX_SHADER);
	vert->compile();

	std::unique_ptr<shader> frag = std::make_unique<shader>(in_fragment_source.data(), GL_FRAGMENT_SHADER);
	frag->compile();

	shader_program curr_shader;
	curr_shader.attach_shader(vert->get_id());
	curr_shader.attach_shader(frag->get_id());
	curr_shader.link();
	curr_shader.use();

	glm::mat4 projection = glm::ortho(0.f, WINDOW_WIDTH, WINDOW_HEIGHT, 0.f, -1.f, 1.f);
	glUniformMatrix4fv(glGetUniformLocation(curr_shader.id(), "projection"), 1, false, glm::value_ptr(projection));
	//m_shaders.insert(std::make_pair(std::string(SPRITE_NAME), std::make_unique<shader_program>(curr_shader)));
	m_shaders.push_back(std::make_unique<shader_program>(curr_shader));
	

	vert->destroy();
	frag->destroy();
}

void resource_module::load_textures() {
	create_texture(TEX_ADDRESS_SHIP, TEX_NAME_SHIP);
	create_texture(TEX_ADDRESS_ENEMY, TEX_NAME_ENEMY);
	create_texture(TEX_ADDRESS_METEOR_BROWN_BIG, TEX_NAME_METEOR_BROWN_BIG);
	create_texture(TEX_ADDRESS_METEOR_BROWN_MED, TEX_NAME_METEOR_BROWN_MED);

}

void resource_module::create_texture(const char *in_tex_address, const char *in_tex_name) {
	int width, height, nr_channels;
	unsigned char *texture_data = load_texture(in_tex_address, width, height, nr_channels);

	texture new_tex;
	new_tex.init_data(texture_data, width, height, nr_channels);

	m_textures.insert(std::make_pair(std::string(in_tex_name), std::make_unique<texture>(new_tex)));

	free_texture_data(texture_data);
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

unsigned char *resource_module::load_texture(const char *in_tex_address, int &out_width, int &out_height, int &out_channels) {
	return stbi_load(in_tex_address, &out_width, &out_height, &out_channels, 0);
}

void resource_module::free_texture_data(unsigned char *in_data) {
	stbi_image_free(in_data);
}
