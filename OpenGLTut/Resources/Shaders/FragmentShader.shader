#version 460 core

out vec4 FinalColor;

in vec3 vertexPos;
in vec2 TexCoord;
uniform sampler2D Texture;
void main()
{
	FinalColor = texture(Texture, TexCoord);
}