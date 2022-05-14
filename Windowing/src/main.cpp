//its needed to include opengl32.lib on Linker -> Additional dependencies OR #include <GL/freeglut.h> manually, to call OpenGl Functions like 'glClear'
#include <GL/glew.h> //bring the openGl header functions in the right version of the hardware
#include <GLFW/glfw3.h>
#include <iostream>
#include "Shader-setup.h"
#include "GLDebugMessageCallback.h"
#include "VertexBuffer.h"
#include "indexBuffer.h"
#include "VertexArray.h"


void drawTriangle() {

	float positions[6] = {
		-.5, -.5,
		.0, .5,
		.5, -.5
	};

	unsigned int vertex_buffer;
	glGenBuffers(1, &vertex_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
	glBufferData(GL_ARRAY_BUFFER, 3 * 2 * sizeof(float), positions, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, false, sizeof(float) * 2, 0);
	glEnableVertexAttribArray(0);
}

void calcAnimation(float& r, float& inc) {
	if (r > 1.) {
		inc = -.05;
	}
	if (r < 0.) {
		inc = .05;
	}
	r += inc;
}

VertexArray* DrawSquare() {
	VertexArray* VAO = new VertexArray;
	VAO->Bind(); //all VBO en IBO have to be created while VAO is on bound

	float positions[] = {
	-.5f, -.5f,
	 .5f, -.5f,
	 .5f, .5f,
	-.5f, .5f,
	};
	VertexBuffer vb(positions, 4 * 2 * sizeof(float));

	VertexBufferLayout layout;
	layout.Push({ GL_FLOAT,  2, GL_FALSE });

	VAO->AddBuffer(vb, layout);

	unsigned int index[] = {
		0,1,2,
		2,3,0
	};
	IndexBuffer idxb(index, 6);

	VAO->AddIdxBuffer(idxb);


	VAO->Unbind();
	return VAO;
}

void deleteOpenGLObjects(std::vector<VertexArray*> vaoDestructionList) {
	for (auto vrtxArray : vaoDestructionList) {
		delete vrtxArray;
	}
}

int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit()) {
		std::cout << "Error Initializing GLfW!\n";
		exit(-1);
	}

	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE); // Enables debugging of openGL context

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(1920, 1080, "Triangle", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	//glfwSwapInterval(1);

	/* Initialize glew (MUST BE AFTER context initialization)*/
	if (glewInit() != GLEW_OK)
		std::cout << "Error Initializing GLEW!\n";

	std::cout << "OpenGl version " << glGetString(GL_VERSION) << std::endl << std::endl;

	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(GLDebugMessageCallback, NULL);


	//--------------------------------------------------------------------------------------------------------------
	{
		//VertexArray VAO;
		//VAO.Bind(); //all VBO en IBO have to be created while VAO is on bound

		//float positions[] = {
		//-.5f, -.5f,
		// .5f, -.5f,
		// .5f, .5f,
		//-.5f, .5f,
		//};
		//VertexBuffer vb(positions, 4 * 2 * sizeof(float));

		//VertexBufferLayout layout;
		//layout.Push({ GL_FLOAT,  2, GL_FALSE });

		//VAO.AddBuffer(vb, layout);

		//unsigned int index[] = {
		//0,1,2,
		//2,3,0
		//};
		//IndexBuffer idxb(
		//	index, 6);

		//VAO.Unbind();
	}
	//--------------------------------------------------------------------------------------------------------------

	std::vector< VertexArray*> vaoDestructionList;
	VertexArray* vaoSquare = DrawSquare();

	vaoDestructionList.push_back(vaoSquare);

	unsigned int shadersProgram = SetupShaders();

	int u_MyColorLocation = glGetUniformLocation(shadersProgram, "u_MyColor");
	glUseProgram(0); //clear program in use;

	//------
	float r = 0.;
	float inc = .05;
	//------

	while (!glfwWindowShouldClose(window))	/* Loop until the user closes the window */
	{
		//processInput(window);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shadersProgram);
		glUniform4f(u_MyColorLocation, .5, r, 1., 1.);

		vaoSquare->Bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr); ////"drawing with index"

		calcAnimation(r, inc);

		glfwSwapBuffers(window);	/* Swap front and back buffers */

		glfwPollEvents();	/* Poll for and process events */
	}

	glDeleteProgram(shadersProgram);
	deleteOpenGLObjects(vaoDestructionList);
	glfwTerminate();
	return 0;
}