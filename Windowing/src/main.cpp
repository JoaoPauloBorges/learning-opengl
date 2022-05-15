//its needed to include opengl32.lib on Linker -> Additional dependencies OR #include <GL/freeglut.h> manually, to call OpenGl Functions like 'glClear'
#include "Bootstrap.h"
#include "objectDrawers/HouseDrawer.h"
#include "objectDrawers/SquareDrawer.h"


int main(void)
{
	GLFWwindow* window = Bootstrap::Setup();

	HouseDrawer drawer;

	SquareDrawer sd;

	//clear program in use;
	glUseProgram(0);

	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);

		drawer.Draw();
		sd.Draw();

		glfwSwapBuffers(window);/* Swap front and back buffers */
		glfwPollEvents();/* Poll for and process events */
	}

	drawer.Dispose();
	sd.Dispose();
	Bootstrap::Terminate();
	return 0;
}