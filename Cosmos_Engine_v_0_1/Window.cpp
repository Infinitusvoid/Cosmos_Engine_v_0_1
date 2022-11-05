#include "Window.h"

#include <iostream>

void Window::init_and_configure()
{
	//glfw: initialize and configure
	// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void Window::create()
{
	// glfw window creation
	// --------------------
	window = glfwCreateWindow(width, height, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return;
	}
	glfwMakeContextCurrent(window);




	//Set callbacks
	//glfwSetFramebufferSizeCallback(window, Engine::framebuffer_size_callback);
	//glfwSetCursorPosCallback(window, Engine::mouse_callback);
	//glfwSetScrollCallback(window, Engine::scroll_callback);


	capture_mouse();

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return;
	}

	// configure global opengl state
	// -----------------------------
	glEnable(GL_DEPTH_TEST);
}

void Window::capture_mouse()
{
	// tell GLFW to capture our mouse
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Window::clear()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}