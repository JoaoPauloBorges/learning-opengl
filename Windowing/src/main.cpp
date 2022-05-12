//its needed to include opengl32.lib on Linker -> Additional dependencies OR #include <GL/freeglut.h> manually, to call OpenGl Functions like 'glClear'
#include <GL/glew.h> //bring the openGl header functions in the right version of the hardware
#include <GLFW/glfw3.h>
#include <iostream>
#include "Shader-setup.h"
#include "GLDebugMessageCallback.h"


void drawSquare() {
	//defining the vertex buffer
	float positions[] = {
		-.5f, -.5f,
		 .5f, -.5f,
		 .5f, .5f,
		-.5f, .5f,
	};

	unsigned int index[] = {
		0,1,2,
		2,3,0
	};

	unsigned int buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	//passing data to the buffer
	glBufferData(GL_ARRAY_BUFFER, 4 * 2 * sizeof(float), positions, GL_STATIC_DRAW);

	// defining index 
	unsigned int indexBufferObject;
	glGenBuffers(1, &indexBufferObject);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferObject);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), index, GL_STATIC_DRAW);

	// defining the layout of the buffer (what each part of the arrays represents, and their sizes in the array)
	// VERTEX is the group of attributes that define a point, like position, texture mapping and normals
	// 
	// @params
	// index: "index of the vertex" ,
	// size: "how many positions in the buffer represents the attributes"
	// type: "type of the data",
	// normalyzed: "booleand that indicates if tha data have to be normalized"
	// stride: "the total (including all attributes) amount of bytes between each vertex",
	// pointer: "amount of bytes to reach the next attr"
	glVertexAttribPointer(0, 2, GL_FLOAT, false, sizeof(float) * 2, 0);
	glEnableVertexAttribArray(0);
}

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

void draw() {
	//glDrawArrays(GL_TRIANGLES, 0, 3);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr); ////"drawing with index"
};

int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit()) {
		std::cout << "Error Initializing GLfW!\n";
		exit(-1);
	}

	// Enables debugging of openGL context
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(1920, 1080, "Triangle", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	/* Initialize glew (MUST BE AFTER context initialization)*/
	if (glewInit() != GLEW_OK)
		std::cout << "Error Initializing GLEW!\n";

	std::cout << "OpenGl version " << glGetString(GL_VERSION) << std::endl << std::endl;

	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(GLDebugMessageCallback, NULL);

	unsigned int shaders = SetupShaders();

	drawSquare();

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		draw();

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glDeleteProgram(shaders);

	glfwTerminate();
	return 0;
}