#version 330 core
//this executes for almost avery pixel
in vec4 gl_FragCoord;

out vec4 color;

void main()
{
	if ((int(gl_FragCoord.y) % 2) != 0) {
		color = vec4(0., 0., 0., 1.);
	}
	else {
		color = vec4(1., 0., 1., 1.);
	}
};
