#include "HouseDrawer.h"
#include <iostream>
#include <vector>
#include <gl/glew.h>
#include "../VertexBuffer.h"
#include "../VertexBufferLayout.h"
#include "../VertexArray.h"

HouseDrawer::HouseDrawer() {
	Setup();
}

void HouseDrawer::Setup()
{
	float positions[] = {
	-1.5f, -.5f, 0., 0.,
	-.5f, -.5f,	1., 0.,
	-.5f, .5f, 1., 1.,
	-1.5f, .5f, 0., 1.,
	};

	unsigned int idx[] = {
		0,1,2,2,3,0,
	};

	float positions2[] = {
		.5, -.5, 0., 0.,
		1.5, -.5, 1., 0,
		1.5, .5, 1., 1.,
		.5, .5, 0., 1.
	};


	va1 = CreateVertexArray(positions, 4 * 4 * sizeof(float), idx, 6);
	va2 = CreateVertexArray(positions2, 4 * 4 * sizeof(float), idx, 6);

	shader = new Shader("assets/shaders/Texture/vsTexture.shader", "assets/shaders/Texture/fsTexture.shader");
}

void HouseDrawer::Draw()
{
	shader->Bind();
	shader->SetUniform1i("u_Texture", 0);

	va1->Bind();
	glDrawElements(GL_TRIANGLES, va1->idxBuffers[0].GetCount(), GL_UNSIGNED_INT, nullptr); ////"drawing with index"


	va2->Bind();
	glDrawElements(GL_TRIANGLES, va1->idxBuffers[0].GetCount(), GL_UNSIGNED_INT, nullptr); ////"drawing with index"
}


void HouseDrawer::CreateBuffers(VertexArray* va, void* data, int dataSize, unsigned int* idx, int idxSize)
{
	VertexBuffer vb(data, dataSize);
	VertexBufferLayout layout;

	layout.Push({ GL_FLOAT,  2, GL_FALSE });
	layout.Push({ GL_FLOAT,  2, GL_FALSE });

	va->AddBuffer(vb, layout);

	IndexBuffer idxb(idx, idxSize);
	va->AddIdxBuffer(idxb);

	Texture texture("assets/textures/dolly_texture.png");
	va->AddTexture(texture);
}

void HouseDrawer::Dispose()
{
	delete va1;
	delete va2;
	delete shader;
}

HouseDrawer::~HouseDrawer() {
	std::cout << "~HouseDrawer" << std::endl;
}

