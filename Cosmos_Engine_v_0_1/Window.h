#pragma once


#include <glad/glad.h>
#include <GLFW/glfw3.h>


struct Window
{
	int width;
	int height;
	GLFWwindow* window;


	void init_and_configure();
	
	void create();
	
	void capture_mouse();
	
	void clear();

};
