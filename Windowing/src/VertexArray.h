#pragma once
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"



class VertexArray {
private:
	unsigned int m_rendererID;
	std::vector<VertexBuffer> vertexBuffers;
	std::vector<IndexBuffer> idxBuffers;

	void DeleteOpenGLBuffer();
public:
	VertexArray();
	~VertexArray();

	void AddBuffer(VertexBuffer& vb, const VertexBufferLayout& layout);
	void AddIdxBuffer(IndexBuffer idxb);

	void Bind() const;
	void Unbind() const;
};