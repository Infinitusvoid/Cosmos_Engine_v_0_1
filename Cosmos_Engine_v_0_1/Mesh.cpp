#include "Mesh.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <numbers>
#include <string>
#include <fstream>

void MeshT_::Mesh::add_vertices(float x, float y, float z, float u, float v)
{
	vertices.push_back(x);
	vertices.push_back(y);
	vertices.push_back(z);
	vertices.push_back(u);
	vertices.push_back(v);
}

void MeshT_::Mesh::create()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// texture coord attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
}

void MeshT_::Mesh::bind()
{
	glBindVertexArray(VAO);
}

void MeshT_::Mesh::draw()
{
	glDrawArrays(GL_TRIANGLES, 0, vertices.size());
}

void MeshT_::Mesh::free()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	vertices.clear();
}

void MeshT_::add_quad(Mesh& mesh, glm::vec3 a, glm::vec3 b, glm::vec3 c, glm::vec3 d)
{
	mesh.add_vertices(a.x, a.y, a.z, 0.0f, 0.0f);
	mesh.add_vertices(d.x, d.y, d.z, 1.0f, 0.0f);
	mesh.add_vertices(b.x, b.y, b.z, 0.0f, 1.0f);

	mesh.add_vertices(d.x, d.y, d.z, 1.0f, 0.0f);
	mesh.add_vertices(c.x, c.y, c.z, 1.0f, 1.0f);
	mesh.add_vertices(b.x, b.y, b.z, 0.0f, 1.0f);
}

void MeshT_::scale(Mesh& mesh, float scale)
{
	int elements = mesh.vertices.size() / 5;
	for (int i = 0; i < elements; i++)
	{
		mesh.vertices[i * 5 + 0] = mesh.vertices[i * 5 + 0] * scale;
		mesh.vertices[i * 5 + 1] = mesh.vertices[i * 5 + 1] * scale;
		mesh.vertices[i * 5 + 2] = mesh.vertices[i * 5 + 2] * scale;
	}
}

void MeshT_::build_section(Mesh& mesh, glm::vec3 a, glm::vec3 b, float length, float radius)
{
	glm::vec3 offset = glm::vec3(0.0f, 0.0f, 1.0f);

	const int sections = 25;
	float step = (std::numbers::pi * 2.0f) / sections;


	for (int i = 0; i < sections; i++)
	{
		float t0 = step * i;

		float sig_0_x = sinf(t0);
		float sig_0_y = cosf(t0);

		float t1 = step * (i + 1);

		float sig_1_x = sinf(t1);
		float sig_1_y = cosf(t1);

		glm::vec3 ab = b - a;

		glm::vec3 v1 = glm::cross(ab, glm::vec3(0, 1.0f, 0.0f));
		glm::vec3 v1n = glm::normalize(v1);
		glm::vec3 u1 = glm::cross(v1n, ab);
		glm::vec3 u1n = glm::normalize(u1);

		//glm::vec3 v_a = glm::scale(u1n* + v1n * glm::vec3(y0, y0, y0);
	   // glm::vec3 v_d = u1n * glm::vec3(x1, x1, x1) + v1n * glm::vec3(y1, y1, y1);
	   // glm::vec3 v_c = v_a + ab;
		//glm::vec3 v_b = v_d + ab;

		u1n *= radius;
		v1n *= radius;

		glm::vec3 v_a = a + glm::vec3(sig_0_x, sig_0_x, sig_0_x) * v1n + glm::vec3(sig_0_y, sig_0_y, sig_0_y) * u1n;
		glm::vec3 v_d = a + glm::vec3(sig_1_x, sig_1_x, sig_1_x) * v1n + glm::vec3(sig_1_y, sig_1_y, sig_1_y) * u1n;
		glm::vec3 v_b = v_a + ab * length;
		glm::vec3 v_c = v_d + ab * length;
		add_quad(mesh, v_a, v_b, v_c, v_d);
	}
}

void MeshT_::build_section_001(Mesh& mesh, glm::vec3 a, glm::vec3 b, float length, float radius)
{
	glm::vec3 offset = glm::vec3(0.0f, 0.0f, 1.0f);

	const int sections = 25;
	float step = (std::numbers::pi * 2.0f) / sections;


	for (int i = 0; i < sections; i++)
	{
		float t0 = step * i;

		float sig_0_x = sinf(t0);
		float sig_0_y = cosf(t0);

		float t1 = step * (i + 1);

		float sig_1_x = sinf(t1);
		float sig_1_y = cosf(t1);

		glm::vec3 ab = b - a;

		glm::vec3 v1 = glm::cross(ab, glm::vec3(0, 1.0f, 0.0f));
		glm::vec3 v1n = glm::normalize(v1);
		glm::vec3 u1 = glm::cross(v1n, ab);
		glm::vec3 u1n = glm::normalize(u1);

		//glm::vec3 v_a = glm::scale(u1n* + v1n * glm::vec3(y0, y0, y0);
	   // glm::vec3 v_d = u1n * glm::vec3(x1, x1, x1) + v1n * glm::vec3(y1, y1, y1);
	   // glm::vec3 v_c = v_a + ab;
		//glm::vec3 v_b = v_d + ab;

		u1n *= radius;
		v1n *= radius;

		glm::vec3 v_a = a + glm::vec3(sig_0_x, sig_0_x, sig_0_x) * v1n + glm::vec3(sig_0_y, sig_0_y, sig_0_y) * u1n;
		glm::vec3 v_d = a + glm::vec3(sig_1_x, sig_1_x, sig_1_x) * v1n + glm::vec3(sig_1_y, sig_1_y, sig_1_y) * u1n;
		glm::vec3 v_b = v_a + ab * length;
		glm::vec3 v_c = v_d + ab * length;
		add_quad(mesh, v_a, v_b, v_c, v_d);
	}
}

void MeshT_::export_to_file(Mesh& mesh)
{
	const char* path = "C:\\Users\\CosmosXYZ\\Desktop\\export_obj\\test.obj";



	std::string result;
	result.reserve(20000000);

	int number_of_floats = mesh.vertices.size();
	int number_of_vertices = number_of_floats / 5;
	int number_of_triangles = number_of_vertices / 3;

	int offset_indice = 1;


	result.append("# v0.obj\n");
	result.append("#\n");
	result.append("\n");
	result.append("g v0\n");


	for (int i = 0; i < number_of_vertices; i++)
	{
		float x = mesh.vertices[i * 5 + 0];
		float y = mesh.vertices[i * 5 + 1];
		float z = mesh.vertices[i * 5 + 2];
		float u = mesh.vertices[i * 5 + 3];
		float v = mesh.vertices[i * 5 + 4];



		result.append("v");
		result.append(" ");
		result.append(std::to_string(x));
		result.append(" ");
		result.append(std::to_string(y));
		result.append(" ");
		result.append(std::to_string(z));
		result.append("\n");
	}

	result.append("\n");

	for (int i = 0; i < number_of_vertices; i++)
	{
		float x = mesh.vertices[i * 5 + 0];
		float y = mesh.vertices[i * 5 + 1];
		float z = mesh.vertices[i * 5 + 2];
		float u = mesh.vertices[i * 5 + 3];
		float v = mesh.vertices[i * 5 + 4];



		result.append("vt");
		result.append(" ");
		result.append(std::to_string(u));
		result.append(" ");
		result.append(std::to_string(v));
		result.append("\n");
	}

	result.append("\n");

	for (int i = 0; i < number_of_triangles; i++)
	{
		int index_0 = i * 3 + 0;
		float index_0_x = index_0 * 5 + 0;
		float index_0_y = index_0 * 5 + 1;
		float index_0_z = index_0 * 5 + 2;

		int index_1 = i * 3 + 1;
		float index_1_x = index_1 * 5 + 0;
		float index_1_y = index_1 * 5 + 1;
		float index_1_z = index_1 * 5 + 2;

		/*int index_2 = i * 3 + 2;
		float index_2_x = index_2 * 5 + 0;
		float index_2_y = index_2 * 5 + 1;
		float index_2_z = index_2 * 5 + 2;*/


		float a_x = mesh.vertices[index_0_x];
		float a_y = mesh.vertices[index_0_y];
		float a_z = mesh.vertices[index_0_z];

		float b_x = mesh.vertices[index_1_x];
		float b_y = mesh.vertices[index_1_y];
		float b_z = mesh.vertices[index_1_z];

		float n_x = a_y * b_z - a_z * b_y;
		float n_y = a_z * b_x - a_x * b_z;
		float n_z = a_x * b_y - a_y * b_x;

		glm::vec3 n = glm::vec3(n_x, n_y, n_z);
		n = glm::normalize(n);
		n_x = n.x;
		n_y = n.y;
		n_z = n.z;

		result.append("vn");
		result.append(" ");
		result.append(std::to_string(n_x));
		result.append(" ");
		result.append(std::to_string(n_y));
		result.append(" ");
		result.append(std::to_string(n_z));
		result.append("\n");

		result.append("vn");
		result.append(" ");
		result.append(std::to_string(n_x));
		result.append(" ");
		result.append(std::to_string(n_y));
		result.append(" ");
		result.append(std::to_string(n_z));
		result.append("\n");

		result.append("vn");
		result.append(" ");
		result.append(std::to_string(n_x));
		result.append(" ");
		result.append(std::to_string(n_y));
		result.append(" ");
		result.append(std::to_string(n_z));
		result.append("\n");

	}

	result.append(" \n");
	result.append("g\n");

	int offset = 0;
	for (int i = 0; i < number_of_triangles; i++)
	{
		offset += 1;
		result.append("f ");
		result.append(std::to_string(offset));
		result.append("/");
		result.append(std::to_string(offset));
		result.append("/");
		result.append(std::to_string(offset));
		result.append(" ");

		offset += 1;
		result.append(std::to_string(offset));
		result.append("/");
		result.append(std::to_string(offset));
		result.append("/");
		result.append(std::to_string(offset));
		result.append(" ");

		offset += 1;
		result.append(std::to_string(offset));
		result.append("/");
		result.append(std::to_string(offset));
		result.append("/");
		result.append(std::to_string(offset));

		result.append("\n");

	}

	//write to file
	std::ofstream out(path);
	out << result;
	out.close();

}

int MeshT_::num_of_floats(const Mesh& mesh)
{
	return mesh.vertices.size();
}

int MeshT_::number_of_vertices(const Mesh& mesh)
{
	return mesh.vertices.size() / 5;
}

int MeshT_::number_of_triangles(const Mesh& mesh)
{
	return mesh.vertices.size() / (5 * 3);
}


