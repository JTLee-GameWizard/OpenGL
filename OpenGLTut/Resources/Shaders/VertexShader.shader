#version 460 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 aTexCoord;
out vec3 vertexPos;

uniform mat4 modelMat;

out vec2 TexCoord;

void main()
{
	gl_Position = modelMat * vec4(aPos, 1.0);
	vertexPos = aPos;
	TexCoord = aTexCoord;
}