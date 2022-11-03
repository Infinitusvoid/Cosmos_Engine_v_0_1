#include "Tunel_Builder.h"

#include <numbers>

Tunel_Builder_::Tunel_Builder::Tunel_Builder(glm::vec3 pos, int set_number_section)
{
	current_pos = pos;
	first_time = true;
	number_section = set_number_section;
}

void Tunel_Builder_::Tunel_Builder::jump(glm::vec3 pos)
{
	current_pos = pos;
	first_time = true;
	ring_previus.clear();
	ring_next.clear();
}

void Tunel_Builder_::Tunel_Builder::build_to(Mesh_indexed_::Mesh_indexed& mesh_indexed, glm::vec3 next, float radius)
{
	//glm::vec3 ab = b - a;
	glm::vec3 ab = current_pos - next;
	if (glm::length(ab) < std::numeric_limits<float>().epsilon())
	{
		return;
	}
	glm::vec3 v1 = glm::cross(ab, glm::vec3(0, 1.0f, 0.0f));
	glm::vec3 v1n = glm::normalize(v1);
	glm::vec3 u1 = glm::cross(v1n, ab);
	glm::vec3 u1n = glm::normalize(u1);

	//const int number_section = 7;
	const float step = 1.0f / number_section;
	const float step_rot = step * std::numbers::pi * 2.0f;

	//const float radius = 1.0f;//1.0f;
	const float length = 1.0f;

	for (int i = 0; i < number_section; i++)
	{


		float t0 = step_rot * i;

		float sig_0_x = sinf(t0);
		float sig_0_y = cosf(t0);

		/*glm::vec3 v_a = a + glm::vec3(sig_0_x, sig_0_x, sig_0_x) * v1n + glm::vec3(sig_0_y, sig_0_y, sig_0_y) * u1n;
		glm::vec3 v_d = a + glm::vec3(sig_1_x, sig_1_x, sig_1_x) * v1n + glm::vec3(sig_1_y, sig_1_y, sig_1_y) * u1n;
		glm::vec3 v_b = v_a + ab * length;
		glm::vec3 v_c = v_d + ab * length;*/

		glm::vec3 pos = next + glm::vec3(sig_0_x, sig_0_x, sig_0_x) * v1n * radius + glm::vec3(sig_0_y, sig_0_y, sig_0_y) * u1n * radius;
		ring_next.push_back(pos);
	}

	if (first_time)
	{
		first_time = false;
		for (int i = 0; i < number_section; i++)
		{
			float t0 = step_rot * i;

			float sig_0_x = sinf(t0);
			float sig_0_y = cosf(t0);

			/*glm::vec3 v_a = a + glm::vec3(sig_0_x, sig_0_x, sig_0_x) * v1n + glm::vec3(sig_0_y, sig_0_y, sig_0_y) * u1n;
			glm::vec3 v_d = a + glm::vec3(sig_1_x, sig_1_x, sig_1_x) * v1n + glm::vec3(sig_1_y, sig_1_y, sig_1_y) * u1n;
			glm::vec3 v_b = v_a + ab * length;
			glm::vec3 v_c = v_d + ab * length;*/

			glm::vec3 pos =
				next +
				glm::vec3(sig_0_x, sig_0_x, sig_0_x) * v1n * radius + glm::vec3(sig_0_y, sig_0_y, sig_0_y) * u1n * radius +
				ab * length;
			ring_previus.push_back(pos);
		}
	}

	if (first_time == false) //TODO : redundant remove this after testing
	{
		for (int i = 1; i < number_section; i++)
		{
			glm::vec3 v_a = ring_previus[i - 1];
			glm::vec3 v_b = ring_next[i - 1];
			glm::vec3 v_c = ring_next[i];
			glm::vec3 v_d = ring_previus[i];


			Mesh_indexed_::add_quad(mesh_indexed, v_a, v_b, v_c, v_d);//Mesh_::add_quad(mesh, v_a, v_b, v_c, v_d);
		}


		glm::vec3 v_a = ring_previus[0];
		glm::vec3 v_b = ring_next[0];
		glm::vec3 v_c = ring_next[number_section - 1];
		glm::vec3 v_d = ring_previus[number_section - 1];
		Mesh_indexed_::add_quad(mesh_indexed, v_a, v_b, v_c, v_d);//Mesh_::add_quad(mesh, v_a, v_b, v_c, v_d);

	}


	ring_previus.swap(ring_next);
	ring_next.clear();

	//
	current_pos = next;
}

void Tunel_Builder_::Tunel_Builder::build_to(MeshT_::Mesh& mesh, glm::vec3 next, float radius)
{
	//glm::vec3 ab = b - a;
	glm::vec3 ab = current_pos - next;
	if (glm::length(ab) < std::numeric_limits<float>().epsilon())
	{
		return;
	}
	glm::vec3 v1 = glm::cross(ab, glm::vec3(0, 1.0f, 0.0f));
	glm::vec3 v1n = glm::normalize(v1);
	glm::vec3 u1 = glm::cross(v1n, ab);
	glm::vec3 u1n = glm::normalize(u1);

	//const int number_section = 7;
	const float step = 1.0f / number_section;
	const float step_rot = step * std::numbers::pi * 2.0f;

	//const float radius = 1.0f;//1.0f;
	const float length = 1.0f;

	for (int i = 0; i < number_section; i++)
	{


		float t0 = step_rot * i;

		float sig_0_x = sinf(t0);
		float sig_0_y = cosf(t0);

		/*glm::vec3 v_a = a + glm::vec3(sig_0_x, sig_0_x, sig_0_x) * v1n + glm::vec3(sig_0_y, sig_0_y, sig_0_y) * u1n;
		glm::vec3 v_d = a + glm::vec3(sig_1_x, sig_1_x, sig_1_x) * v1n + glm::vec3(sig_1_y, sig_1_y, sig_1_y) * u1n;
		glm::vec3 v_b = v_a + ab * length;
		glm::vec3 v_c = v_d + ab * length;*/

		glm::vec3 pos = next + glm::vec3(sig_0_x, sig_0_x, sig_0_x) * v1n * radius + glm::vec3(sig_0_y, sig_0_y, sig_0_y) * u1n * radius;
		ring_next.push_back(pos);
	}

	if (first_time)
	{
		first_time = false;
		for (int i = 0; i < number_section; i++)
		{
			float t0 = step_rot * i;

			float sig_0_x = sinf(t0);
			float sig_0_y = cosf(t0);

			/*glm::vec3 v_a = a + glm::vec3(sig_0_x, sig_0_x, sig_0_x) * v1n + glm::vec3(sig_0_y, sig_0_y, sig_0_y) * u1n;
			glm::vec3 v_d = a + glm::vec3(sig_1_x, sig_1_x, sig_1_x) * v1n + glm::vec3(sig_1_y, sig_1_y, sig_1_y) * u1n;
			glm::vec3 v_b = v_a + ab * length;
			glm::vec3 v_c = v_d + ab * length;*/

			glm::vec3 pos =
				next +
				glm::vec3(sig_0_x, sig_0_x, sig_0_x) * v1n * radius + glm::vec3(sig_0_y, sig_0_y, sig_0_y) * u1n * radius +
				ab * length;
			ring_previus.push_back(pos);
		}
	}

	if (first_time == false) //TODO : redundant remove this after testing
	{
		for (int i = 1; i < number_section; i++)
		{
			glm::vec3 v_a = ring_previus[i - 1];
			glm::vec3 v_b = ring_next[i - 1];
			glm::vec3 v_c = ring_next[i];
			glm::vec3 v_d = ring_previus[i];

			MeshT_::add_quad(mesh, v_a, v_b, v_c, v_d);
		}


		glm::vec3 v_a = ring_previus[0];
		glm::vec3 v_b = ring_next[0];
		glm::vec3 v_c = ring_next[number_section - 1];
		glm::vec3 v_d = ring_previus[number_section - 1];
		MeshT_::add_quad(mesh, v_a, v_b, v_c, v_d);
		//Mesh_::add_quad(mesh, v_b, v_a, v_d, v_c);
	}


	ring_previus.swap(ring_next);
	ring_next.clear();

	//
	current_pos = next;
}
