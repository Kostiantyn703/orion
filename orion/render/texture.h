#ifndef TEXTURE_H
#define TEXTURE_H

class texture {
public:
	texture();
	texture(texture &tex);

	texture &operator=(const texture &tex);

	void init_data(unsigned char *data, const int &width, const int &height, const int &channels);

	unsigned int get_id() const { return id; }
	int get_width() const { return width; }
	int get_height() const { return height; }

	void bind();
	void unbind();

private:
	unsigned int id;
	unsigned int target;
	unsigned int format;

	int width;
	int height;
	int channels;

	void create();
};
#endif // TEXTURE_H
