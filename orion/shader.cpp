#include "shader.h"

#include "SDL_log.h"

bool shader::compile() {
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

	m_vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(m_vertex, 1, &vertexShaderSource, nullptr);
	glCompileShader(m_vertex);
	int success;
	char info_log[512];

	glGetShaderiv(m_vertex, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(m_vertex, 512, nullptr, info_log);
		SDL_Log(info_log);
		return false; 
	}
	
	m_fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(m_fragment, 1, &fragmentShaderSource, nullptr);
	glCompileShader(m_fragment);
	glGetShaderiv(m_fragment, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(m_fragment, 512, nullptr, info_log);
		SDL_Log(info_log);
		return false;
	}

	m_program = glCreateProgram();
	glAttachShader(m_program, m_vertex);
	glAttachShader(m_program, m_fragment);
	glLinkProgram(m_program);

	glGetProgramiv(m_program, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(m_program, 512, nullptr, info_log);
		SDL_Log(info_log);
	}
	glDeleteShader(m_vertex);
	glDeleteShader(m_fragment);


	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		-0.5f, -0.5f, 0.0f, // left  
		 0.5f, -0.5f, 0.0f, // right 
		 0.0f,  0.5f, 0.0f  // top   
	};

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);


	return true;
}

void shader::draw() const  {
	// draw our first triangle
	glUseProgram(m_program);
	glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
	glDrawArrays(GL_TRIANGLES, 0, 3);
}
