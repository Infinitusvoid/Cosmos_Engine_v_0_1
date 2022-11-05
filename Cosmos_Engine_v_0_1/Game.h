#pragma once

#include "Engine.h"
#include "Mesh.h"
#include "Mesh_indexed.h"
#include "Tunel_Builder.h"
#include "Cam.h"
#include "Mover.h"
#include "Shader.h"
#include "Texture.h"

#include <functional>

namespace Game
{
	// settings
	const unsigned int SCR_WIDTH = 1980;
	const unsigned int SCR_HEIGHT = 1080;

	namespace Models_data_
	{
		namespace D_000_
		{
			void add_verts(std::function<void(float, float, float, float, float)> f);
		}
	}

	namespace Shader_source_
	{
		Shaders_::Shader create_shader();
	}

	namespace Time_calc
	{
		void update();
		float get_delta_time();

	};

	namespace Last_mouse_XY
	{
		void update(double xposIn, double yposIn);
		
		float get_x_offset();
		
		float get_y_offset();
	}

	namespace Build_versions
	{
		void build_version_000(MeshT_::Mesh& mesh);
		
		void build_version_001(MeshT_::Mesh& mesh);
		
		void build_version_002(Mesh_indexed_::Mesh_indexed& mesh_indexed);
	}

	// camera

	Cam_::Camera* get_cam();

	// glfw: whenever the window size changed (by OS or user resize) this callback function executes
	// ---------------------------------------------------------------------------------------------
	void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	
}

