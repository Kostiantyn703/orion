#ifndef SHADER_H
#define SHADER_H

class shader {
public:
	shader(const char *shader_source, const unsigned int shader_type);
	~shader() {}

	unsigned int get_id() const { return m_id; }

	bool compile();
	void destroy();

private:
	unsigned int m_id;

	bool log_errors(const unsigned int check_type);

	shader() = delete;
};
#endif // SHADER_H
