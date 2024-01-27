#ifndef SCRIPT_MODULE_H
#define SCRIPT_MODULE_H

#include <string>

#include "SDL_Log.h"

class script_module {
public:
	script_module();
	~script_module();

	void collect_scripts(const std::string &in_path);

};
#endif // SCRIPT_MODULE_H
