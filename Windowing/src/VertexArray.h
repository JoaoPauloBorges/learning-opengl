#pragma once
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "OpenGLDisposable.h"
#include "Texture.h"




class VertexArray: public OpenGLDisposable {
private:
	unsigned int m_rendererID;
	std::vector<VertexBuffer> vertexBuffers;
	std::vector<Texture> textures;
	
	void DisposeOpenGLChildrenResource();
public:
	std::vector<IndexBuffer> idxBuffers;
	VertexArray();
	~VertexArray();

	void AddBuffer(VertexBuffer& vb, const VertexBufferLayout& layout);
	void AddIdxBuffer(IndexBuffer& idxb);
	void AddTexture(Texture& tex);
	void Bind() const;
	void Unbind() const;

	// Inherited via OpenGLDisposable
	virtual void Dispose() override;
};