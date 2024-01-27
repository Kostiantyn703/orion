#ifndef SCRIPT_MODULE_H
#define SCRIPT_MODULE_H

#include "SDL_Log.h"

class script_module {
public:
	script_module() { SDL_Log("Script module constructed"); }
	~script_module() {}

};

#endif // SCRIPT_MODULE_H
