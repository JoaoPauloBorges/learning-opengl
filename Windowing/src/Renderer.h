#pragma once
#include <GLFW/glfw3.h>

namespace Renderer
{
	void Clear();
	void ProcessInput();
}

namespace Renderer
{

	void Clear() {
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void Renderer::ProcessInput() {

	}
}