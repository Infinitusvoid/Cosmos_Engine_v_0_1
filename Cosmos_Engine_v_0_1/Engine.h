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

#include "Mesh.h"
#include "Mesh_indexed.h"
#include "Tunel_Builder.h"
#include "Cam.h"
#include "Mover.h"
#include "Shader.h"
#include "Texture.h"

#include <functional>

namespace Engine
{
	// settings
	const unsigned int SCR_WIDTH = 1980;
	const unsigned int SCR_HEIGHT = 1080;

	namespace Time_calc
	{
		void update();
		float get_delta_time();
	};
}

