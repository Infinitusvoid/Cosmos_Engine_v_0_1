#include "Mesh_indexed.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <numbers>
#include <string>
#include <fstream>

void Mesh_indexed_::Mesh_indexed::create()
{

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * indeces.size(), indeces.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);
}

void Mesh_indexed_::Mesh_indexed::draw()
{
	glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
	//glDrawArrays(GL_TRIANGLES, 0, 6);
	glDrawElements(GL_TRIANGLES, counter, GL_UNSIGNED_INT, 0);
	// glBindVertexArray(0); // no need to unbind it every time 
}

int Mesh_indexed_::Mesh_indexed::add_vertex(float x, float y, float z, float u, float v)
{
	vertices.push_back(x);
	vertices.push_back(y);
	vertices.push_back(z);
	vertices.push_back(u);
	vertices.push_back(v);
	counter += 1;
	return counter;
}

void Mesh_indexed_::Mesh_indexed::add_triangle(const int index_a, int index_b, int index_c)
{
	indeces.push_back(index_a);
	indeces.push_back(index_b);
	indeces.push_back(index_c);
}

void Mesh_indexed_::Mesh_indexed::free()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	vertices.clear();
	indeces.clear();
	counter = -1;
}

void Mesh_indexed_::add_quad(Mesh_indexed& mesh_indexed, const glm::vec3 a, const glm::vec3 b, const glm::vec3 c, const glm::vec3 d)
{
	//vertex_reuse

	int index_a = mesh_indexed.add_vertex(a.x, a.y, a.z, 0.0f, 0.0f);
	int index_b = mesh_indexed.add_vertex(b.x, b.y, b.z, 0.0f, 1.0f);
	int index_c = mesh_indexed.add_vertex(c.x, c.y, c.z, 1.0f, 1.0f);
	int index_d = mesh_indexed.add_vertex(d.x, d.y, d.z, 1.0f, 0.0f);

	mesh_indexed.add_triangle(index_a, index_d, index_b);
	mesh_indexed.add_triangle(index_d, index_c, index_b);

	//no reuse
	/*
	mesh_indexed.add_vertex(a.x, a.y, a.z, 0.0f, 0.0f);
	mesh_indexed.add_vertex(d.x, d.y, d.z, 1.0f, 0.0f);
	mesh_indexed.add_vertex(b.x, b.y, b.z, 0.0f, 1.0f);

	mesh_indexed.add_vertex(d.x, d.y, d.z, 1.0f, 0.0f);
	mesh_indexed.add_vertex(c.x, c.y, c.z, 1.0f, 1.0f);
	mesh_indexed.add_vertex(b.x, b.y, b.z, 0.0f, 1.0f);
	*/
}

void Mesh_indexed_::Debug::add_test_quad(Mesh_indexed& mesh_indexed)
{

	int a = mesh_indexed.add_vertex(0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	int b = mesh_indexed.add_vertex(0.0f, 1.0f, 0.0f, 0.0f, 1.0f);
	int c = mesh_indexed.add_vertex(1.0f, 1.0f, 0.0f, 1.0f, 1.0f);
	int d = mesh_indexed.add_vertex(1.0f, 0.0f, 0.0f, 1.0f, 0.0f);

	mesh_indexed.add_triangle(a, b, d);
	mesh_indexed.add_triangle(b, c, d);

	//float vertices_internal[] = {
	//		 0.0f,  0.0f, 0.0f,  0.0f, 0.0f, //a
	//		 0.0f, 1.0f, 0.0f,  0.0f, 1.0f, // b
	//		1.0f, 1.0f, 0.0f,  1.0f, 1.0f, // c
	//		1.0f,  0.0f, 0.0f , 1.0f, 0.0f  // d
	//};

	//unsigned int indices_invernal[] = {  // note that we start from 0!
	//0, 1, 3,  // first Triangle
	//1, 2, 3   // second Triangle
	//};
}