#version 330 core

layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec2 vertexUV;
layout(location = 2) in vec3 vertexNormal;

out vec3 fragmentColor;
out vec2 UV;

uniform mat4 mm;
uniform mat4 vm;
uniform mat4 pm;
uniform mat3 it;
uniform vec3 lightDir;
uniform float lightAmo;

void main()
{
    gl_Position = pm * vm * mm * vec4(vertexPosition_modelspace, 1);
	vec3 nor = normalize(it * vertexNormal);
	float nd = max(0.0, dot(nor, lightDir));
	fragmentColor = vec3(1.0, 1.0, 1.0);// * nd;
	UV = vertexUV;
}