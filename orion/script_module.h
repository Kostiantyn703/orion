#ifndef SCRIPT_MODULE_H
#define SCRIPT_MODULE_H

#include <string>

#include "SDL_Log.h"

class script_module {
public:
	script_module();
	~script_module();

	void collect_scripts(const std::string &in_path);
private:
	bool get_file_content(const std::string &in_file, std::string &out_content);
};
#endif // SCRIPT_MODULE_H
