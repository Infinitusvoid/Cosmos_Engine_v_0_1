#pragma once


#include <glad/glad.h>
#include <GLFW/glfw3.h>



#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <numbers>
#include <deque>
#include <fstream>
#include <iostream>

#include "Shader.h"
#include "Mesh.h"
#include "Mesh_indexed.h"
#include "Tunel_Builder.h"
#include "Cam.h"
#include "Mover.h"

#include "Texture.h"

#include <functional>

namespace Engine
{
	// settings
	const unsigned int SCR_WIDTH = 1980;
	const unsigned int SCR_HEIGHT = 1080;

	
	namespace Default_shaders
	{
		Shaders_::Shader create_default_shader();
	}

	
	

	namespace Win_
	{
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
	}

	/*
	namespace Mapes
	{
		namespace Map_0_
		{
			void map_0(Win_::Window& window);
		}
	}
	*/

	namespace Models_data_
	{
		void add_verts(std::function<void(float, float, float, float, float)> f);
	}


	// glfw: whenever the window size changed (by OS or user resize) this callback function executes
	// ---------------------------------------------------------------------------------------------
	void framebuffer_size_callback(GLFWwindow* window, int width, int height);

	// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
	// ---------------------------------------------------------------------------------------------------------
	void process_input(GLFWwindow* window);

	// glfw: whenever the mouse moves, this callback is called
	// -------------------------------------------------------
	void mouse_callback(GLFWwindow* window, double xposIn, double yposIn);


	// glfw: whenever the mouse scroll wheel scrolls, this callback is called
	// ----------------------------------------------------------------------
	void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);


	void run();
}

