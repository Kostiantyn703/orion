#version 330 core

out vec4 frag_color;

uniform vec4 shader_color;

void main()
{
	frag_color = shader_color;
}
