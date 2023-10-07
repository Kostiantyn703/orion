#ifndef RESOURCE_MODULE_H
#define RESOURCE_MODULE_H

#include <string>
#include <unordered_map>
#include <memory>

class shader_loader {
public:
	bool load_shader(const char *source_address, std::string &out_shader_source);
};

class resource_module {
	using shader_map = std::unordered_map<std::string, std::string>;
	using texture_map = std::unordered_map<std::string, std::string>;
public:
	resource_module();
	~resource_module();

	void init_shaders();
	bool get_shader_source(const std::string &in_key, std::string &out_value);

	unsigned char *load_texture(int &out_width, int &out_height, int &out_channels);
	void free_texture_data(unsigned char *in_data);

private:
	shader_map m_shader_sources;
	texture_map m_textures;

	std::unique_ptr<shader_loader> m_shader_loader;

};
#endif // RESOURCE_MODULE_H
