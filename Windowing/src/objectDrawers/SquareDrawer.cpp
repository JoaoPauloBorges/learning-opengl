#include "SquareDrawer.h"

float SquareDrawer::calcAnimation()
{
	green+=5;
	if (green == 0 || green == 100)
		green *= -1;
	return abs(green/100.);
}

void SquareDrawer::CreateBuffers(VertexArray* va, void* data, int dataSize, unsigned int* idx, int idxSize)
{
	VertexBuffer vb(data, dataSize);
	VertexBufferLayout layout;

	VertexAttrLayout attr = { GL_FLOAT, 2, GL_FALSE };
	layout.Push(attr);

	IndexBuffer ib(idx, idxSize);

	va->AddBuffer(vb, layout);
	va->AddIdxBuffer(ib);
}

void SquareDrawer::Setup()
{
	float positions[] = {
	-.5f, -.5f,
	.5f, -.5f,
	.5f, .5f,
	-.5f, .5f,
	};

	unsigned int idx[] = {
		0,1,2,2,3,0,
	};

	va1 = CreateVertexArray(positions, 4 * 2 * sizeof(float), idx, 6);

	shader = new Shader("assets/shaders/vs.shader", "assets/shaders/fs.shader");
}

void SquareDrawer::Dispose()
{
	delete va1;
	delete shader;
}

void SquareDrawer::Draw()
{
	va1->Bind();

	shader->Bind();
	shader->SetUniform4f("u_MyColor", .5, calcAnimation(), .8, 1.);
	glDrawElements(GL_TRIANGLES, va1->idxBuffers[0].GetCount(), GL_UNSIGNED_INT, nullptr);
}
