#ifndef RESOURCE_MODULE_H
#define RESOURCE_MODULE_H

#include <string>
#include <unordered_map>
#include <memory>

#include "texture.h"
#include "shader_program.h"

class resource_module {
	using texture_map = std::unordered_map<std::string, std::unique_ptr<texture>>;
public:
	resource_module();
	~resource_module() {}

	texture *get_texture(const std::string &in_key)	const	{	return m_textures.at(in_key).get();	}

	void load_textures();

private:
	texture_map m_textures;
	
	void create_texture(const char *in_tex_address, const char *in_tex_name);
	unsigned char *load_texture(const char *in_tex_address, int &out_width, int &out_height, int &out_channels);
	void free_texture_data(unsigned char *in_data);
};
#endif // RESOURCE_MODULE_H
