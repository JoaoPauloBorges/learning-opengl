#pragma once
#include <string>
#include "OpenGLDisposable.h"
class Texture: public OpenGLDisposable
{
private:
	unsigned int m_RendererID;
	std::string filePath;
	unsigned char* localBuffer;
	int width, height, bpp;
public:

	Texture(const std::string& path, bool keepImgOnCPu = false);
	~Texture();

	void Bind(unsigned int slot = 0) const;
	void Unbind();

	inline int GetWidth() const { return width; }
	inline int GetHeight() const { return height; }

	// Inherited via OpenGLDisposable
	virtual void Dispose() override;
};

