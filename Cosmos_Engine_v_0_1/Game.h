#pragma once

#include "Engine.h"

namespace Game
{
	

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

	// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
	// ---------------------------------------------------------------------------------------------------------
	void process_input(GLFWwindow* window);
	
	// glfw: whenever the mouse moves, this callback is called
	// -------------------------------------------------------
	void mouse_callback(GLFWwindow* window, double xposIn, double yposIn);
	
	
	// glfw: whenever the mouse scroll wheel scrolls, this callback is called
	// ----------------------------------------------------------------------
	void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
	


	namespace Win_
	{
		struct Window
		{
			int width;
			int height;
			GLFWwindow* window;

			void init_and_configure();
			

			void create();
			
			void capture_mouse();
			
			void clear();
			
		};




	}


	namespace Maps_
	{
		namespace Map_0_
		{
			void map_0(Game::Win_::Window& window);
		}
	}

	namespace Sandbox_
	{
		void run();
	}
}

