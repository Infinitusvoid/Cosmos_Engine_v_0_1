#include "Time_Singelton.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Time_Singelton
{
	// timing
	float deltaTime = 0.0f;	// time between current frame and last frame
	float lastFrame = 0.0f;

	void update()
	{
		float currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
	}

	float get_delta_time()
	{
		return deltaTime;
	}
}
