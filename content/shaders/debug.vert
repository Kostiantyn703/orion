#version 330 core

layout (location = 0) in vec4 in_pos;

uniform mat4 aabb_model;
uniform mat4 projection;

void main()
{
	gl_Position = projection * aabb_model * vec4(in_pos.xy, 0.f, 1.f);
}
