
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Util.h"

static unsigned int CompileShader(unsigned int type, const std::string& source) {

	unsigned int shaderId = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(shaderId, 1, &src, NULL);
	glCompileShader(shaderId);

	int success;
	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
	if (!success) {
		int length;
		glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &length);
		char* message = new char[length];
		glGetShaderInfoLog(shaderId, length, &length, message);
		std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!" << std::endl;
		std::cout << message << std::endl;
		delete[] message;
		glDeleteShader(shaderId);

		return 0;
	}

	return shaderId;
}

static unsigned int CreateProgramWithShaders(const std::string& vertexShader, const std::string& fragmentShader) {
	const unsigned int program = glCreateProgram();
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	//glDetachShader(program, vs);
	//glDetachShader(program, fs);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}

unsigned int SetupShaders() {
	std::string vertexShader = loadfile("assets/shaders/vs.shader");
	std::string FragmentShader = loadfile("assets/shaders/fs.shader");

	unsigned int program = CreateProgramWithShaders(vertexShader, FragmentShader);
	glUseProgram(program);
	return program;
}

