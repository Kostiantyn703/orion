#ifndef SCRIPT_MODULE_H
#define SCRIPT_MODULE_H

#include <string>
#include <vector>

class script_module {
public:
	script_module();
	~script_module();

	void collect_scripts(const std::string &in_path, std::vector<float> &out_data);
private:
	bool get_file_content(const std::string &in_file, std::string &out_content);

	float parse_float(std::string &in_line);
};
#endif // SCRIPT_MODULE_H
