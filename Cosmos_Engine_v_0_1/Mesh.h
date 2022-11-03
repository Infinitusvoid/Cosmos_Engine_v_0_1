#pragma once

#include <vector>
#include "glm/glm.hpp"

namespace MeshT_
{
	struct Mesh {
		std::vector<float> vertices;

		unsigned int VAO;
		unsigned int VBO;

		void add_vertices(float x, float y, float z, float u, float v);
		

		void create();
		

		void bind();
		

		void draw();
		

		void free();
		
	};

	void add_quad(Mesh& mesh, glm::vec3 a, glm::vec3 b, glm::vec3 c, glm::vec3 d);
	

	void scale(Mesh& mesh, float scale);
	

	void build_section(Mesh& mesh, glm::vec3 a, glm::vec3 b, float length, float radius);
	

	void build_section_001(Mesh& mesh, glm::vec3 a, glm::vec3 b, float length, float radius);
	


	void export_to_file(Mesh& mesh);
	

	int num_of_floats(const Mesh& mesh);
	

	int number_of_vertices(const Mesh& mesh);
	

	int number_of_triangles(const Mesh& mesh);
	


}


