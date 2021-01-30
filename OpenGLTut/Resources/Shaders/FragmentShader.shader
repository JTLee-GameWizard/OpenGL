#version 460 core

out vec4 FinalColor;

in vec3 vertexPos;

void main()
{
	FinalColor = vec4(1.0, 0.5, 0.3, 1.0) + vec4(vertexPos, 0.0);
}