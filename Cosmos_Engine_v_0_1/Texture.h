#pragma once

struct Texture
{
	unsigned int texture_ID;

	void load_RGB(const char* path);


	void load_RGBA(const char* path);


	void bind_to_texture_unit_0();

	void bind_to_texture_unit_1();

};
