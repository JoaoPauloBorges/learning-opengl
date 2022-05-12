#version 330 core
//this executes once for each vertex

layout(location = 0) in vec4 position;

void main()
{
	gl_Position = position;
};
