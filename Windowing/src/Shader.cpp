#include "Shader.h"
#include <GL/glew.h>
#include <iostream>
#include "Util.h"

Shader::Shader(const std::string& vsFilePath, const std::string& fsFilePath) :
	vertexShaderFilePath(vsFilePath),
	fragmentShaderFilePath(fsFilePath)
{
	std::string vertexShader = loadfile(vertexShaderFilePath);
	std::string fragmentShader = loadfile(fragmentShaderFilePath);

	m_RendererId = CreateProgramWithShaders(vertexShader, fragmentShader);
}

Shader::~Shader() {
	std::cout << "Calling Shader Destroyer and Deletign OpenGl shaders program" << std::endl;
	glDeleteProgram(m_RendererId);
}


unsigned int Shader::CompileShader(unsigned int type, const std::string& source) {
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

unsigned int Shader::CreateProgramWithShaders(const std::string& vertexShader, const std::string& fragmentShader) {
	const unsigned int program = glCreateProgram();
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}

void Shader::SetUniform4f(const std::string& uniform_name, float v0, float v1, float v2, float v3) {
	glUniform4f(GetUniformLocation(uniform_name), v0, v1, v2, v3);
}

void Shader::Bind() {
	glUseProgram(m_RendererId);
}

void Shader::Unbind() {
	glUseProgram(0);
}

int Shader::GetUniformLocation(const std::string& uniform_name) {
	if (uniformsLocationCache.find(uniform_name) != uniformsLocationCache.end()) {
		return uniformsLocationCache[uniform_name];
	}

	int location = glGetUniformLocation(m_RendererId, uniform_name.c_str());
	if (location == -1) {
		std::cout << "[WARNING] Uniform " << uniform_name << " doesn't exist or is not in use on the shader" << std::endl;
	}
	uniformsLocationCache[uniform_name] = location;
	return location;
}