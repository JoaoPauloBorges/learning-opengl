#include "VertexArray.h"
#include <iostream>

VertexArray::VertexArray() {
	glGenVertexArrays(1, &m_rendererID);
	//Bind();
}

VertexArray::~VertexArray() {
	std::cout << "~VertexArray" << std::endl;
	Dispose();
}

void VertexArray::DisposeOpenGLChildrenResource() {
	for (auto& vertx : vertexBuffers) {
		vertx.Dispose();
	}
	for (auto& idxBuff : idxBuffers) {
		idxBuff.Dispose();
	}
	for (auto& tex : textures) {
		tex.Dispose();
	}
}

void VertexArray::AddIdxBuffer(IndexBuffer& idxb) {
	idxBuffers.push_back(idxb);
}

void VertexArray::AddTexture(Texture& tex)
{
	textures.push_back(tex);
}

void VertexArray::AddBuffer(VertexBuffer& vb, const VertexBufferLayout& layout) {
	vertexBuffers.push_back(vb);

	const std::vector<VertexAttrLayout>& attrLayouts = layout.GetAttrLayouts();

	unsigned int offset = 0;

	for (unsigned int i = 0; i < attrLayouts.size(); i++) {
		const VertexAttrLayout attrLayout = attrLayouts[i];
		// defining the layout of the buffer (what each part of the arrays represents, and their sizes in the array)
		// VERTEX is the group of attributes that define a point, like position, texture mapping and normals
		// 
		// @params
		// index: "index of the vertex in the vertex array" ,
		// size: "how many positions in the buffer represents the attribute"
		// type: "type of the data",
		// normalyzed: "booleand that indicates if tha data have to be normalized"
		// stride: "the total (including all attributes) amount of bytes between each vertex",
		// pointer: "amount of bytes to reach the next attr"

		glEnableVertexAttribArray(i);
		const auto stride = layout.GetStride();
		const auto sb = attrLayout.GetSizeInBytes();
		glVertexAttribPointer(i, attrLayout.size, attrLayout.dataType, attrLayout.normalized, stride, (const void*)offset);
		offset += sb;
	}
}

void VertexArray::Bind() const {
	glBindVertexArray(m_rendererID);
	for (auto& tex : textures) {
		tex.Bind();
	}
}

void VertexArray::Unbind() const {
	glBindVertexArray(0);

}

void VertexArray::Dispose()
{
	std::cout << "Disposing VertexArray" << std::endl;
	DisposeOpenGLChildrenResource();
	glDeleteVertexArrays(1, &m_rendererID);
}
