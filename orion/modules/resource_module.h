#ifndef RESOURCE_MODULE_H
#define RESOURCE_MODULE_H

#include <string>
#include <unordered_map>
#include <memory>

#include "../render/texture.h"

class resource_module {
	using texture_map = std::unordered_map<std::string, std::unique_ptr<texture>>;
public:
	static resource_module *get_instance();

	texture *get_texture(const std::string &key) const { return textures.at(key).get();	}

	void load_textures();
	bool load_shader(const char *source_address, std::string &shader_source);

private:
	resource_module();

	static resource_module *instance;

	texture_map textures;
	
	void create_texture(const char *tex_address, const char *tex_name);
	unsigned char *load_texture(const char *tex_address, int &width, int &height, int &channels);
	void free_texture_data(unsigned char *data);
};
#endif // RESOURCE_MODULE_H
