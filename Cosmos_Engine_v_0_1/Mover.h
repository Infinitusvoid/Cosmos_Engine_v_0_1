#pragma once

#include <glm/glm.hpp>

struct Mover
{
	glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 direction = glm::vec3(1.0f, 0.0f, 0.0f);
	float speed = 1.0f;

	void move();
	
	void randomize_direction();
	

	void jump(glm::vec3 pos);

	void clear_direction();
	
};
