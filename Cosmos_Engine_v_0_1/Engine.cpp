#include "Engine.h"



namespace Engine
{
	namespace Time_calc
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
	
	
	Cam_::Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
	Cam_::Camera* get_cam()
	{
		return &camera;
	}

}