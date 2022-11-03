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

struct Texture
{
	unsigned int texture_ID;

	void load_RGB(const char* path);
	

	void load_RGBA(const char* path);
	

	void bind_to_texture_unit_0();
	
	void bind_to_texture_unit_1();
	
};
