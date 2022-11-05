// OpenGL_Exploring_and_learning.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include "Game.h"




namespace Sandbox_
{
	
	

	
	


	void run()
	{
		Game::Win_::Window window;
		window.width = Game::SCR_WIDTH;
		window.height = Game::SCR_HEIGHT;
		window.init_and_configure();
		window.create();

		//scene_0(window);
		Game::Maps_::Map_0_::map_0(window);
		// glfw: terminate, clearing all previously allocated GLFW resources.
		// ------------------------------------------------------------------
		glfwTerminate();
	}


}

int main()
{
	Sandbox_::run();
}
