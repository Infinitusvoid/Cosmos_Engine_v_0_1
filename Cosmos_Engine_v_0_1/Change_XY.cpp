#include "Change_XY.h"



Change_XY::Change_XY(float center_x, float center_y)
{
	lastX = center_x;
	lastY = center_y;
}

void Change_XY::update(double xposIn, double yposIn)
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

float Change_XY::get_x_offset()
{
	return xoffset;
}

float Change_XY::get_y_offset()
{
	return yoffset;
}
