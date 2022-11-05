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


	namespace Last_mouse_XY
	{
		float lastX = Engine::SCR_WIDTH / 2.0f;
		float lastY = Engine::SCR_HEIGHT / 2.0f;
		bool firstMouse = true;

		float xoffset = 0.0f;
		float yoffset = 0.0f;

		void update(double xposIn, double yposIn)
		{
			float xpos = static_cast<float>(xposIn);
			float ypos = static_cast<float>(yposIn);

			if (firstMouse)
			{
				lastX = xpos;
				lastY = ypos;
				firstMouse = false;
			}

			xoffset = xpos - lastX;
			yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

			lastX = xpos;
			lastY = ypos;
		}

		float get_x_offset()
		{
			return xoffset;
		}

		float get_y_offset()
		{
			return yoffset;
		}

	}



	void framebuffer_size_callback(GLFWwindow* window, int width, int height)
	{
		std::cout << "Window width : " << width << " height : " << height << std::endl;
		// make sure the viewport matches the new window dimensions; note that width and 
		// height will be significantly larger than specified on retina displays.
		glViewport(0, 0, width, height);
	}

	void process_input(GLFWwindow* window)
	{
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, true);

		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			(*Engine::get_cam()).ProcessKeyboard(Cam_::Camera_Movement::FORWARD, Engine::Time_calc::get_delta_time());
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			(*Engine::get_cam()).ProcessKeyboard(Cam_::Camera_Movement::BACKWARD, Engine::Time_calc::get_delta_time());
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			(*Engine::get_cam()).ProcessKeyboard(Cam_::Camera_Movement::LEFT, Engine::Time_calc::get_delta_time());
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			(*Engine::get_cam()).ProcessKeyboard(Cam_::Camera_Movement::RIGHT, Engine::Time_calc::get_delta_time());
	}

	void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
	{
		Engine::Last_mouse_XY::update(xposIn, yposIn);

		(*Engine::get_cam()).ProcessMouseMovement(Engine::Last_mouse_XY::get_x_offset(), Engine::Last_mouse_XY::get_y_offset());
	}

	void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
	{
		(*Engine::get_cam()).ProcessMouseScroll(static_cast<float>(yoffset));
	}
}