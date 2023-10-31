#version 330 core

out vec4 frag_color;

in vec2 out_texture;

uniform sampler2D texture;

void main()
{
	frag_color = vec4(1.f, 0.f, 0.f, 1.f);//texture(texture, out_texture);
}