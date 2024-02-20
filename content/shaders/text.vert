#version 330 core

layout (location = 0) in vec4 in_vertex;

out vec2 tex_coords;

uniform mat4 projection;

void main()
{
	gl_Position = projection * vec4(in_vertex.xy, 0.0, 1.0);
	tex_coords = in_vertex.zw;
}