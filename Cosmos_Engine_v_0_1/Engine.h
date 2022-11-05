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
	namespace Models_data_
	{
		void add_verts(std::function<void(float, float, float, float, float)> f);
	}

	void run();
}

