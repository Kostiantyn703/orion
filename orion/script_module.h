#ifndef SCRIPT_MODULE_H
#define SCRIPT_MODULE_H

#include <string>
#include <vector>

#include "game_block.h"

class script_module {
public:
	script_module();
	~script_module();

	void collect_scripts(const std::string &in_path, std::vector<game_block> &out_data);
private:
	bool get_file_content(const std::string &in_file, std::string &out_content);
	void parse_file_content(std::string &in_content, game_block &out_block);
	
	float parse_float(std::string &in_line);
	size_t parse_int(std::string &in_line);
};
#endif // SCRIPT_MODULE_H
