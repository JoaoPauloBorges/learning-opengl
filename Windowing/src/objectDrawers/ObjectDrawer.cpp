#include "ObjectDrawer.h"

VertexArray* ObjectDrawer::CreateVertexArray(void* data, int dataSize, unsigned int* idx, int idxSize) {
	VertexArray* va = new VertexArray;
	va->Bind(); //all VBO en IBO have to be created while VAO is on bound

	CreateBuffers(va, data, dataSize, idx, idxSize);

	va->Unbind();
	return va;
}

void ObjectDrawer::CreateBuffers(VertexArray* va, void* data, int dataSize, unsigned int* idx, int idxSize)
{

}