#version 330 core

layout (location = 0) in vec4 in_pos;

out vec2 out_texture;
out float scroll_offset;

uniform mat4 model;
uniform mat4 projection;
uniform vec2 scalar;
uniform float scroll;

void main()
{
	gl_Position = projection * model * vec4(in_pos.xy, 0.f, 1.f);
	out_texture = vec2(in_pos.z / scalar.x, in_pos.w / scalar.y);
	out_texture.y -= scroll;
}
