#version 330 core
//this executes for almost every pixel

uniform vec4 u_MyColor;

out vec4 vertexColor;

void main()
{
	vertexColor = u_MyColor;
};
