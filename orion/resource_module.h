#ifndef RESOURCE_MODULE_H
#define RESOURCE_MODULE_H

#include <string>
#include <unordered_map>
#include <memory>

#include "texture.h"
#include "shader_program.h"

class resource_module {
	using shader_map = std::unordered_map<std::string, std::unique_ptr<shader_program>>;
	using texture_map = std::unordered_map<std::string, std::unique_ptr<texture>>;
public:
	resource_module();
	~resource_module();

	texture			*get_texture(const std::string &in_key)	{	return m_textures.at(in_key).get();	}
	shader_program	*get_shader	(const std::string &in_key)	{	return m_shaders.at(in_key).get();	}
	
	void init_shaders();
	void compile_shaders(const std::string &in_vertex_source, const std::string &in_fragment_source);
	
	void load_textures();
	void free_texture_data(unsigned char *in_data);

private:
	shader_map m_shaders;
	texture_map m_textures;

	bool load_shader(const char *source_address, std::string &out_shader_source);
	unsigned char *load_texture(int &out_width, int &out_height, int &out_channels);
};
#endif // RESOURCE_MODULE_H
