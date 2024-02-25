#ifndef TEXTURE_H
#define TEXTURE_H

class texture {
public:
	texture();
	texture(texture &in_texture);

	texture &operator=(const texture &in_texture);
	~texture() {}

	void init_data(unsigned char *in_data, const int &in_width, const int &in_height, const int &in_channels);

	unsigned int id()	const	{	return m_id;	}
	int get_width()		const	{	return m_width;	}
	int get_height()	const	{	return m_height;}

	void bind();
	void unbind();

private:
	unsigned int m_id;
	unsigned int m_target;
	unsigned int m_format;

	int m_width;
	int m_height;
	int m_channels;

	void create();
};
#endif // TEXTURE_H
