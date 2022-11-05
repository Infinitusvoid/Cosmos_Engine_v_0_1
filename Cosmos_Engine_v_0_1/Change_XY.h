#pragma once

class Change_XXX
{
public:
	
	Change_XXX(float center_x, float center_y);
	
	void update(double xposIn, double yposIn);
	
	float get_x_offset();
	
	float get_y_offset();

private:
	float lastX;
	float lastY;
	bool firstMouse = true;

	float xoffset = 0.0f;
	float yoffset = 0.0f;

};

