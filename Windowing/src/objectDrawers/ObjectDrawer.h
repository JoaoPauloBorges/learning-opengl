#pragma once
#include "../VertexArray.h"
#include <iostream>

class ObjectDrawer {
protected:
	virtual void CreateBuffers(VertexArray* va, void* data, int dataSize, unsigned int* idx, int idxSize) = 0;
	VertexArray* CreateVertexArray(void* data, int dataSize, unsigned int* idx, int idxSize);

public:
	virtual void Setup() = 0;
	virtual void Dispose() = 0;
	virtual void Draw() = 0;
};