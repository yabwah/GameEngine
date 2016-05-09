#version 130


in vec4 fragmentColor;
in vec2 fragmentPosition;

out vec4 color;

uniform float time;

void main()
{
	color = vec4(fragmentColor.r * (cos(fragmentPosition.x * time) + 1) * 0.5,
	             fragmentColor.g * (cos(fragmentPosition.y * time * 4.0) + 1) * 0.5,
				 fragmentColor.b * (cos(fragmentPosition.x * time * 8.0) + 1) * 0.5,
				 fragmentColor.a);
				 
}