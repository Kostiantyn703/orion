#include "render_module.h"

#include "SDL.h"
#include "glad/glad.h"

#include "shader_program.h"
#include "shader.h"
#include "vertex_buffer.h"

#define log_error	if (SDL_GetError()[0]) {SDL_LogError(0, SDL_GetError()); }

const char *vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
const char *fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n\0";

render_module::render_module() {
	init();
}

render_module::~render_module() {}

void render_module::init() {
	SDL_InitSubSystem(SDL_INIT_VIDEO);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	log_error;
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	log_error;

	m_window = std::make_unique<window>();
	glClearColor(0.1f, 0.1f, 0.3f, 1.f);
	
	std::unique_ptr<shader> vert = std::make_unique<shader>(vertexShaderSource, GL_VERTEX_SHADER);
	vert->compile();
	std::unique_ptr<shader> frag = std::make_unique<shader>(fragmentShaderSource, GL_FRAGMENT_SHADER);
	frag->compile();

	m_shader_program = std::make_unique<shader_program>();
	m_shader_program->attach_shader(vert->get_id());
	m_shader_program->attach_shader(frag->get_id());
	m_shader_program->link();

	vert->destroy();
	frag->destroy();

	m_vertex_array = std::make_unique<vertex_array>();
	std::unique_ptr<vertex_buffer> VBO = std::make_unique<vertex_buffer>();
	m_vertex_array->bind();
	VBO->init_data();
	m_vertex_array->init_data();

	VBO->unbind();
	m_vertex_array->unbind();
}

void render_module::run() {
	glClear(GL_COLOR_BUFFER_BIT);
	m_shader_program->use();
	m_vertex_array->bind();
	glDrawArrays(GL_TRIANGLES, 0, 3);
	m_window->swap();
}