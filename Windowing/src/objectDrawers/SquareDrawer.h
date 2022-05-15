#pragma once
#include "ObjectDrawer.h"
#include "../Shader.h"
class SquareDrawer : public ObjectDrawer
{
private:
	VertexArray* va1;
	Shader* shader;

	float green = 0;

	float calcAnimation();
public:
	SquareDrawer() { Setup(); }
	~SquareDrawer() { std::cout << "~SquareDrawer" << std::endl; }
	// Inherited via ObjectDrawer
	virtual void CreateBuffers(VertexArray* va, void* data, int dataSize, unsigned int* idx, int idxSize) override;
	virtual void Setup() override;
	virtual void Dispose() override;
	virtual void Draw() override;
};

