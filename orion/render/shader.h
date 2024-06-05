#ifndef SHADER_H
#define SHADER_H

class shader {
public:
	shader(const char *shader_source, const unsigned int shader_type);

	bool compile();
	void destroy();

	unsigned int get_id() const { return id; }

private:
	unsigned int id;

	bool log_errors(const unsigned int check_type);
};
#endif // SHADER_H
