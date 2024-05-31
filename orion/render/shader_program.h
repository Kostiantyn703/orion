#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H

class shader_program {
public:
	shader_program();

	unsigned int get_id() const { return id; }

	void use();
	void attach_shader(unsigned int shader_id);
	void link();

private:
	unsigned int id;

	void create();
};
#endif // SHADER_PROGRAM_H
