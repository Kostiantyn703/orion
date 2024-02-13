#version 330 core

out vec4 frag_color;

in vec2 out_texture;
in float scroll_offset;

uniform sampler2D texture;

void main()
{
	frag_color = texture(texture, out_texture);
}
