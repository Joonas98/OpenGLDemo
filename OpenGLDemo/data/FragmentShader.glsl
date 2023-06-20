#version 330 core

in vec3 fragmentColor;
in vec2 UV;

out vec3 color;

uniform sampler2D mainTex;

void main()
{
	color = fragmentColor * texture( mainTex, UV ).rgb;
}