#include "Mover.h"

void Mover::move()
{
	position += direction * speed;
}

void Mover::randomize_direction()
{
	float dx = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	float dy = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	float dz = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	direction += glm::vec3(dx - 0.5f, dy - 0.5f, dz - 0.5f) * 0.25f;

	direction = glm::normalize(direction);
}

void Mover::jump(glm::vec3 pos)
{
	position = pos;
}

void Mover::clear_direction()
{
	direction = glm::vec3(0.0f, 0.0f, 0.0f);
}
