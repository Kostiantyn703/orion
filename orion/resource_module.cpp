#include "resource_module.h"

#include <iostream>
#include <fstream>
#include <sstream>

#include "SDL_log.h"
#include "globals.h"


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
