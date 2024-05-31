#ifndef BUFFER_OBJECT_H
#define BUFFER_OBJECT_H

#include "glad/glad.h"

class buffer_object {
public:
	buffer_object(unsigned int target);
	~buffer_object();

	template<typename T>
	void init_data(T &data);

	void bind();
	void unbind();

private:
	unsigned int id;
	unsigned int target;

	void create();
};

template<typename T>
void buffer_object::init_data(T &data) {
	glBufferData(target, sizeof(data), &data, GL_STATIC_DRAW);
}
#endif // BUFFER_OBJECT_H
