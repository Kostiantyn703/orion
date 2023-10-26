#ifndef BUFFER_OBJECT_H
#define BUFFER_OBJECT_H

#include "glad/glad.h"
#include <vector>

class buffer_object {
public:
	buffer_object(unsigned int in_target);
	~buffer_object();

	template<typename T>
	void init_data(const std::vector<T> &in_data);
	template<typename T>
	void init_data(T &in_data);

	void bind();
	void unbind();

private:
	unsigned int m_id;
	unsigned int m_target;

	void create();
};

template<typename T>
void buffer_object::init_data(const std::vector<T> &in_data) {
	bind();
	glBufferData(m_target, sizeof(in_data), in_data.data(), GL_STATIC_DRAW);
}

template<typename T>
void buffer_object::init_data(T &in_data) {
	bind();
	glBufferData(m_target, sizeof(in_data), &in_data, GL_STATIC_DRAW);
}

#endif // BUFFER_OBJECT_H
