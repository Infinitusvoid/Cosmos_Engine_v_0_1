#include "Game.h"








void Game::Sandbox_::run()
{
	Engine::Win_::Window window;
	window.width = Engine::SCR_WIDTH;
	window.height = Engine::SCR_HEIGHT;
	window.init_and_configure();
	window.create();

	//scene_0(window);
	Engine::Mapes::Map_0_::map_0(window);
	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
}
