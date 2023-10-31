#version 330 core

layout (location = 0) in vec4 in_pos;

//out vec2 out_texture;

uniform mat4 model;
uniform mat4 projection;

void main()
{
	gl_Position = projection * model * vec4(in_pos.xy, 0.f, 1.f);
	//out_texture = vec2(in_pos.z, in_pos.w);
}
