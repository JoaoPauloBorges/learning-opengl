#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "GLDebugMessageCallback.h"


namespace Bootstrap {

	GLFWwindow* Setup();
	void Terminate();
}

namespace Bootstrap {
	GLFWwindow* Setup() {
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
			exit(-1);
		}

		/* Make the window's context current */
		glfwMakeContextCurrent(window);

		//glfwSwapInterval(1);

		/* Initialize glew (MUST BE AFTER context initialization)*/
		if (glewInit() != GLEW_OK)
			std::cout << "Error Initializing GLEW!\n";

		glEnable(GL_DEBUG_OUTPUT);
		glDebugMessageCallback(GLDebugMessageCallback, NULL);

		std::cout << "OpenGl version " << glGetString(GL_VERSION) << std::endl << std::endl;

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		return window;
	}

	void Terminate() {
		glfwTerminate();
	}
}