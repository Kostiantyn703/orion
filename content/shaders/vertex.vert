#version 330 core

layout (location = 0) in vec2 in_pos;
layout (location = 1) in vec2 in_tex;

out vec2 out_texture;

uniform vec2 offset;

void main()
{
	gl_Position = vec4(in_pos, 0.f, 1.f);
	//gl_Position.x += offset.x * 2.f;
	//gl_Position.y += offset.y;

	out_texture = vec2(in_tex.x, in_tex.y);
}
