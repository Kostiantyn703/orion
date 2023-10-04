#version 330 core

layout (location = 0) in vec2 aPos;

uniform vec2 offset;

void main()
{
	gl_Position = vec4(aPos.x, aPos.y, 0.f, 1.f);
	gl_Position.x += offset.x * 2.f;
	gl_Position.y += offset.y;
}
