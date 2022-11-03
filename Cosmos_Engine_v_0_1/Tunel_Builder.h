#pragma once

#include <vector>
#include "glm/glm.hpp"
#include "Mesh_indexed.h"
#include "Mesh.h"

namespace Tunel_Builder_
{

	struct Tunel_Builder
	{
		glm::vec3 current_pos;

		std::vector<glm::vec3> ring_previus;
		std::vector<glm::vec3> ring_next;

		bool first_time;
		int number_section;
		Tunel_Builder(glm::vec3 pos, int set_number_section);
		
		void jump(glm::vec3 pos);
		
		void build_to(Mesh_indexed_::Mesh_indexed& mesh_indexed, glm::vec3 next, float radius);
		
		void build_to(MeshT_::Mesh& mesh, glm::vec3 next, float radius);
		
	};


}