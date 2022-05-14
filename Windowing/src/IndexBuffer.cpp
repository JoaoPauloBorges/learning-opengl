#include "IndexBuffer.h"
#include <GL/glew.h>
#include <iostream>

IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count):
	m_Count(count)
{
	glGenBuffers(1, &m_RendererId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer() {
	std::cout << "calling IndexBuffer Destructor" << std::endl;
}

void IndexBuffer::DeleteOpenGLBuffer() {
	std::cout << "deleting IndexBuffer" << std::endl;
	glDeleteBuffers(1, &m_RendererId);
}


void IndexBuffer::Bind() const {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererId);
}
void IndexBuffer::Unbind() const {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}