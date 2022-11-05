#pragma once

#include "Engine.h"

namespace Game
{
	

	namespace Build_versions
	{
		void build_version_000(MeshT_::Mesh& mesh);
		
		void build_version_001(MeshT_::Mesh& mesh);
		
		void build_version_002(Mesh_indexed_::Mesh_indexed& mesh_indexed);
	}

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

