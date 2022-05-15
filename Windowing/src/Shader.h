#pragma once
#include <string>
#include <unordered_map>
#include "OpenGLDisposable.h"


class Shader: public OpenGLDisposable {
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

	void Bind() const;
	void Unbind() const;
	void SetUniform4f(const std::string& uniform_name, float v0, float v1, float v2, float v3);
	void SetUniform1i(const std::string& uniform_name, int value);
	void SetUniform1f(const std::string& uniform_name, float value);




	// Inherited via OpenGLDisposable
	virtual void Dispose() override;

};