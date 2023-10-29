#ifndef VERTEX_ARRAY_H
#define VERTEX_ARRAY_H

class vertex_array {
public:
	vertex_array();
	~vertex_array() {}

	void init_data();

	void bind();
	void unbind();

private:
	unsigned int m_id;

	void create();
};
#endif // VERTEX_ARRAY_H
