#pragma once
#include <string>
#include <unordered_map>

class Shader {
private:
	unsigned int m_RendererId;

	std::unordered_map<std::string, int> uniformsLocationCache;

	std::string vertexShaderFilePath;
	std::string fragmentShaderFilePath;

	unsigned int CompileShader(unsigned int type, const std::string& source);
	unsigned int CreateProgramWithShaders(const std::string& vertexShader, const std::string& fragmentShader);

	int GetUniformLocation(const std::string& uniform_name);

public:
	Shader(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath);
	~Shader();

	void Bind();
	void Unbind();
	void SetUniform4f(const std::string& uniform_name, float v0, float v1, float v2, float v3);



};