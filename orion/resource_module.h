#ifndef RESOURCE_MODULE_H
#define RESOURCE_MODULE_H

#include <string>
#include <unordered_map>
#include <memory>

class shader_loader {
public:
	bool load_shader();
};

class resource_module {
	using shader_map = std::unordered_map<std::string, std::string>;
public:
	resource_module();
	~resource_module();


private:
	shader_map m_shader_sources;
	std::unique_ptr<shader_loader> m_shader_loader;

};
#endif // RESOURCE_MODULE_H
