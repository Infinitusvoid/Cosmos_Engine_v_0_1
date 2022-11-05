#include "Change_XXX.h"



Change_XXX::Change_XXX(float center_x, float center_y)
{
	lastX = center_x;
	lastY = center_y;
}

void Change_XXX::update(double xposIn, double yposIn)
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

float Change_XXX::get_x_offset()
{
	return xoffset;
}

float Change_XXX::get_y_offset()
{
	return yoffset;
}
