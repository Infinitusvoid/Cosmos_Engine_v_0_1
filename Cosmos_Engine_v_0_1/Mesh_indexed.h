#pragma once


#include <vector>
#include "glm/glm.hpp"

namespace Mesh_indexed_
{
	struct Mesh_indexed
	{


		void create();
		
		void draw();
		

		int add_vertex(float x, float y, float z, float u, float v);
		

		void add_triangle(const int index_a, int index_b, int index_c);
		

		void free();
		

		//TODO create an general way for looping thru mesh_instance ( passing functions as argument, function pointer, lambda etc and remove this out)

		//void export_to_file()
		//{
		//	const char* path = "C:\\Users\\CosmosXYZ\\Desktop\\export_obj\\test.obj";



		//	std::string result;
		//	result.reserve(20000000);

		//	int number_of_floats = vertices.size();
		//	int number_of_vertices = number_of_floats / 5;
		//	int number_of_triangles = number_of_vertices / 3;

		//	int offset_indice = 1;


		//	result.append("# v0.obj\n");
		//	result.append("#\n");
		//	result.append("\n");
		//	result.append("g v0\n");


		//	for (int i = 0; i < number_of_vertices; i++)
		//	{
		//		float x = vertices[i * 5 + 0];
		//		float y = vertices[i * 5 + 1];
		//		float z = vertices[i * 5 + 2];
		//		float u = vertices[i * 5 + 3];
		//		float v = vertices[i * 5 + 4];



		//		result.append("v");
		//		result.append(" ");
		//		result.append(std::to_string(x));
		//		result.append(" ");
		//		result.append(std::to_string(y));
		//		result.append(" ");
		//		result.append(std::to_string(z));
		//		result.append("\n");
		//	}

		//	result.append("\n");

		//	//TODO wodn here goes differently

		//	for (int i = 0; i < number_of_vertices; i++)
		//	{
		//		float x = vertices[i * 5 + 0];
		//		float y = vertices[i * 5 + 1];
		//		float z = vertices[i * 5 + 2];
		//		float u = vertices[i * 5 + 3];
		//		float v = vertices[i * 5 + 4];



		//		result.append("vt");
		//		result.append(" ");
		//		result.append(std::to_string(u));
		//		result.append(" ");
		//		result.append(std::to_string(v));
		//		result.append("\n");
		//	}

		//	result.append("\n");

		//	for (int i = 0; i < number_of_triangles; i++)
		//	{
		//		int index_0 = i * 3 + 0;
		//		float index_0_x = index_0 * 5 + 0;
		//		float index_0_y = index_0 * 5 + 1;
		//		float index_0_z = index_0 * 5 + 2;

		//		int index_1 = i * 3 + 1;
		//		float index_1_x = index_1 * 5 + 0;
		//		float index_1_y = index_1 * 5 + 1;
		//		float index_1_z = index_1 * 5 + 2;

		//		/*int index_2 = i * 3 + 2;
		//		float index_2_x = index_2 * 5 + 0;
		//		float index_2_y = index_2 * 5 + 1;
		//		float index_2_z = index_2 * 5 + 2;*/


		//		float a_x = vertices[index_0_x];
		//		float a_y = vertices[index_0_y];
		//		float a_z = vertices[index_0_z];

		//		float b_x = vertices[index_1_x];
		//		float b_y = vertices[index_1_y];
		//		float b_z = vertices[index_1_z];

		//		float n_x = a_y * b_z - a_z * b_y;
		//		float n_y = a_z * b_x - a_x * b_z;
		//		float n_z = a_x * b_y - a_y * b_x;

		//		glm::vec3 n = glm::vec3(n_x, n_y, n_z);
		//		n = glm::normalize(n);
		//		n_x = n.x;
		//		n_y = n.y;
		//		n_z = n.z;

		//		result.append("vn");
		//		result.append(" ");
		//		result.append(std::to_string(n_x));
		//		result.append(" ");
		//		result.append(std::to_string(n_y));
		//		result.append(" ");
		//		result.append(std::to_string(n_z));
		//		result.append("\n");

		//		result.append("vn");
		//		result.append(" ");
		//		result.append(std::to_string(n_x));
		//		result.append(" ");
		//		result.append(std::to_string(n_y));
		//		result.append(" ");
		//		result.append(std::to_string(n_z));
		//		result.append("\n");

		//		result.append("vn");
		//		result.append(" ");
		//		result.append(std::to_string(n_x));
		//		result.append(" ");
		//		result.append(std::to_string(n_y));
		//		result.append(" ");
		//		result.append(std::to_string(n_z));
		//		result.append("\n");

		//	}

		//	result.append(" \n");
		//	result.append("g\n");

		//	int offset = 0;
		//	for (int i = 0; i < number_of_triangles; i++)
		//	{
		//		offset += 1;
		//		result.append("f ");
		//		result.append(std::to_string(offset));
		//		result.append("/");
		//		result.append(std::to_string(offset));
		//		result.append("/");
		//		result.append(std::to_string(offset));
		//		result.append(" ");

		//		offset += 1;
		//		result.append(std::to_string(offset));
		//		result.append("/");
		//		result.append(std::to_string(offset));
		//		result.append("/");
		//		result.append(std::to_string(offset));
		//		result.append(" ");

		//		offset += 1;
		//		result.append(std::to_string(offset));
		//		result.append("/");
		//		result.append(std::to_string(offset));
		//		result.append("/");
		//		result.append(std::to_string(offset));

		//		result.append("\n");

		//	}

		//	//write to file
		//	std::ofstream out(path);
		//	out << result;
		//	out.close();
		//}

	private:
		int counter = -1;

		std::vector<float> vertices;
		std::vector<int> indeces;

		unsigned int VAO;
		unsigned int VBO;
		unsigned int EBO;
	};

	void add_quad(Mesh_indexed& mesh_indexed, const glm::vec3 a, const glm::vec3 b, const glm::vec3 c, const glm::vec3 d);
	


	namespace Debug
	{
		void add_test_quad(Mesh_indexed& mesh_indexed);
		
	}
}

