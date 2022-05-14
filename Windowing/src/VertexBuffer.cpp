#include "VertexBuffer.h"
#include <GL/glew.h>
#include <iostream>

VertexBuffer::VertexBuffer(const void* data, unsigned int size) {
	glGenBuffers(1, &m_RendererId);
	Bind();
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer() {
	std::cout << "calling VertexBuffer destructor" << std::endl;
}

void VertexBuffer::DeleteOpenGLBuffer() {
	std::cout << "deleting vrtx buffer" << std::endl;
	glDeleteBuffers(1, &m_RendererId);
}

void VertexBuffer::Bind() const {
	glBindBuffer(GL_ARRAY_BUFFER, m_RendererId);
}
void VertexBuffer::Unbind() const {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}