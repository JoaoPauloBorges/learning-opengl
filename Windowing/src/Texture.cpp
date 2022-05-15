#include "Texture.h"
#include "GL/glew.h"
#include "../third-party/STB/stb_image.h"
#include <iostream>

Texture::Texture(const std::string& path, bool keepImgOnCPu) :
	m_RendererID(0),
	filePath(path),
	localBuffer(nullptr),
	width(0),
	height(0),
	bpp(0)
{
	stbi_set_flip_vertically_on_load(1); //opengl maps textures from bottom left not top left, so we flip vertically before.
	localBuffer = stbi_load(path.c_str(), &width, &height, &bpp, 4);

	glGenTextures(1, &m_RendererID);
	Bind();

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //TODO learn more about it
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, localBuffer); //TODO learn more about it
	Unbind();

	if (localBuffer && !keepImgOnCPu) {
		stbi_image_free(localBuffer);
	}
}

Texture::~Texture()
{
	std::cout << " ~Texture" << std::endl;
}

void Texture::Bind(unsigned int slot) const
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, m_RendererID);
}

void Texture::Unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::Dispose()
{
	std::cout << "Disposing Texture" << std::endl;
	glDeleteTextures(1, &m_RendererID);
}
