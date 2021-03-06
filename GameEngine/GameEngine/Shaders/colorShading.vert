#version 130

in vec2 vertexPosition;
in vec4 vertexColor;

out vec4 fragmentColor;
out vec2 fragmentPosition;


void main()
{
	gl_Position.xy = vertexPosition;
	gl_Position.z = 0.0;
	gl_Position.w = 1.0;
	
	fragmentColor = vertexColor;
	fragmentPosition = vertexPosition;
}
