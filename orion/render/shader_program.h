#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H

class shader_program {
public:
	shader_program();
	~shader_program() {}

	unsigned int id()	const	{	return m_id;	}

	void use();
	void attach_shader(unsigned int shader_id);
	void link();

private:
	unsigned int m_id;

	void create();
};
#endif // SHADER_PROGRAM_H
