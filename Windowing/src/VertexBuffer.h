#pragma once
#include "OpenGLDisposable.h"


class VertexBuffer: public OpenGLDisposable {
private:
	unsigned int m_RendererId;
public:
	VertexBuffer(const void* data, unsigned int size);
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;

	// Inherited via OpenGLDisposable
	virtual void Dispose() override;
};