#version 330 core

out vec4 frag_color;

in vec2 out_texture;

uniform sampler2D m_texture;
uniform vec4 shader_color;

void main()
{
	//frag_color = shader_color * texture(m_texture, out_texture);
	frag_color = texture(m_texture, out_texture);
}
