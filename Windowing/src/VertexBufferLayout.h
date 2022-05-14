#pragma once
#include <vector>
#include <GL/glew.h>

struct VertexAttrLayout {
	unsigned int dataType;
	unsigned int size; //how many positions in the array
	int normalized;

	static unsigned int GetSizeOfType(unsigned int type) {

		switch (type)
		{
		case GL_FLOAT: return 4;
		case GL_UNSIGNED_INT: return 4;
		case GL_UNSIGNED_BYTE: return 1;
		}
	}

	inline unsigned int GetSizeInBytes() const { return VertexAttrLayout::GetSizeOfType(dataType)* size; }
};

class VertexBufferLayout {
private:
	std::vector<VertexAttrLayout> m_Elements;
	unsigned int m_Stride;
public:
	VertexBufferLayout() :
		m_Stride(0) {}

	void Push(VertexAttrLayout element) {
		m_Elements.push_back(element);
		m_Stride += element.GetSizeInBytes();
	}

	inline std::vector<VertexAttrLayout> GetAttrLayouts() const { return m_Elements; }

	inline unsigned int GetStride() const { return m_Stride; }
};