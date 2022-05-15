#pragma once
#include "ObjectDrawer.h"
#include "../Shader.h"

class HouseDrawer: public ObjectDrawer {
private:
	VertexArray* va1;
	VertexArray* va2;
	Shader* shader;

public:
	HouseDrawer();
	~HouseDrawer();

	// Inherited via ObjectDrawer
	virtual void Setup() override;
	virtual void Draw() override;
	virtual void CreateBuffers(VertexArray* va, void* data, int dataSize, unsigned int* idx, int idxSize) override;
	virtual void Dispose() override;


};