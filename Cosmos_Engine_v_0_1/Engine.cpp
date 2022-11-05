#include "Engine.h"


#include <glad/glad.h>
#include <GLFW/glfw3.h>



#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <numbers>
#include <deque>
#include <fstream>
#include <functional>
#include <memory>

#include "Shader.h"
#include "Mesh.h"
#include "Mesh_indexed.h"
#include "Tunel_Builder.h"
#include "Cam.h"
#include "Mover.h"

#include "Texture.h"


#include "Time_Singelton.h"

#include "Change_XY.h"

#include "Window.h"
#include "Constants.h"

namespace Engine
{

	//engine components
	Cam_::Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
	Change_XY change_xy(Constants::SCR_WIDTH / 2.0f, Constants::SCR_HEIGHT / 2.0f);


	namespace Build_versions
	{
		void build_version_000(MeshT_::Mesh& mesh)
		{
			//TODO make save last one rotation of data, make it not recompute what it does not have to. 
			//Than you just connect.


			//mesh.vertices.clear();

			MeshT_::scale(mesh, 0.1f);

			glm::vec3 a;
			glm::vec3 b;


			MeshT_::add_quad(mesh, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f));

			glm::vec3 direction = glm::vec3(1, 2, 3);
			glm::vec3 s_a = glm::vec3(0, 0, 0);
			glm::vec3 s_b = glm::vec3(0, 0, 1);
			for (int i = 0; i < 20000; i++)
			{
				s_a = s_b;
				s_b += direction;

				float dx = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
				float dy = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
				float dz = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
				direction += glm::vec3(dx - 0.5f, dy - 0.5f, dz - 0.5f) * 0.25f;

				direction = glm::normalize(direction);

				MeshT_::build_section(mesh, s_a, s_b, 1.0f, 1.0f);
			}

		}

		void build_version_001(MeshT_::Mesh& mesh)
		{
			mesh.vertices.clear();
			//Engine_::Components_::Geometry_::Mesh_::scale(mesh, 0.1f);








			Tunel_Builder_::Tunel_Builder builder(glm::vec3(0.0f, 0.0f, 0.0f), 7);

			/* builder.build_to(mesh, glm::vec3(0, 0, 1), 1.0f);
			 builder.build_to(mesh, glm::vec3(0, 0, 2),1.0f);

			 builder.build_to(mesh, glm::vec3(0, 0, 4),1.0f);

			 builder.build_to(mesh, glm::vec3(0, 0, 8), 1.0f);

			 builder.build_to(mesh, glm::vec3(0, 3, 10), 1.0f);*/

			Mover mover;

			const glm::vec3 jump_position = glm::vec3(0.0f, 0.0f, 10.0f);

			for (int j = 0; j < 25; j++)
			{

				mover.position = glm::vec3(0, 3, 10);
				mover.direction = glm::vec3(1, 0, 0);
				mover.speed = 1.0f;

				builder.jump(jump_position);
				mover.jump(jump_position);
				mover.clear_direction();

				for (int i = 0; i < 100; i++)
				{
					mover.move();
					builder.build_to(mesh, mover.position, 0.25f + 0.20f * sinf(i * 0.001 * 3.1415 * 100.0f));
					mover.randomize_direction();
				}
			}


			MeshT_::export_to_file(mesh);

			//build_section(mesh, glm::vec3(0, 0, 0), glm::vec3(1, 0, 0), 1.0f, 0.1f * 0.5f);
			//build_section(mesh, glm::vec3(0, 0, 0), glm::vec3(1, 1, 0), 1.0f, 0.1f * 0.5f);

		}

		void build_version_002(Mesh_indexed_::Mesh_indexed& mesh_indexed, int seed)
		{
			

			auto rnd_position_around = [&seed](glm::vec3 center, float radius)
			{
				float x = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
				float y = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
				float z = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
				return glm::vec3(x - 0.5f, y - 0.5f, z - 0.5f) * radius;
			};


			std::cout << "RND : " << rnd_position_around(glm::vec3(1.0, 1.0, 1.0), 1.0f).x << " \n";
			//mesh_indexed.clear();

			Tunel_Builder_::Tunel_Builder builder(glm::vec3(0.0f, 0.0f, 0.0f), 7);

			Mover mover;

			glm::vec3 jump_position = glm::vec3(0.0f, 0.0f, 10.0f);

			for (int j = 0; j < 25; j++)
			{

				mover.position = glm::vec3(0, 3 + 5, 10);
				mover.direction = glm::vec3(1, 0, 0);
				mover.speed = 1.0f;

				jump_position = rnd_position_around(glm::vec3(0, 20, 0), 100.0f);

				builder.jump(jump_position);
				mover.jump(jump_position);

				//mover.clear_direction();

				for (int i = 0; i < 100; i++)
				{
					mover.move();
					builder.build_to(mesh_indexed, mover.position, 1.0f + 0.5f * sinf(i * 0.001 * 3.1415 * 200.0f));
					mover.randomize_direction();
				}
			}


			//Engine_::Components_::Geometry_::Mesh_::export_to_file(mesh);
			//mesh_indexed.export_to_file();

		}
	}
	

	

	

	
	
	void framebuffer_size_callback(GLFWwindow* window, int width, int height)
	{
		std::cout << "Window width : " << width << " height : " << height << std::endl;
		// make sure the viewport matches the new window dimensions; note that width and 
		// height will be significantly larger than specified on retina displays.
		glViewport(0, 0, width, height);
	}

	void process_input(GLFWwindow* window)
	{
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, true);

		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			camera.ProcessKeyboard(Cam_::Camera_Movement::FORWARD, Time_Singelton::get_delta_time());
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			camera.ProcessKeyboard(Cam_::Camera_Movement::BACKWARD, Time_Singelton::get_delta_time());
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			camera.ProcessKeyboard(Cam_::Camera_Movement::LEFT, Time_Singelton::get_delta_time());
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			camera.ProcessKeyboard(Cam_::Camera_Movement::RIGHT, Time_Singelton::get_delta_time());
	}
	

	void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
	{
		change_xy.update(xposIn, yposIn);
		camera.ProcessMouseMovement(change_xy.get_x_offset(), change_xy.get_y_offset());
	}

	void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
	{
		camera.ProcessMouseScroll(static_cast<float>(yoffset));
	}
	

	namespace Maps
	{
		
		//TODO

		struct Tunel_Builder
		{
			void build_version_002(Mesh_indexed_::Mesh_indexed& mesh_indexed, int seed)
			{


				auto rnd_position_around = [&seed](glm::vec3 center, float radius)
				{
					float x = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
					float y = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
					float z = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
					return glm::vec3(x - 0.5f, y - 0.5f, z - 0.5f) * radius;
				};


				std::cout << "RND : " << rnd_position_around(glm::vec3(1.0, 1.0, 1.0), 1.0f).x << " \n";
				//mesh_indexed.clear();

				Tunel_Builder_::Tunel_Builder builder(glm::vec3(0.0f, 0.0f, 0.0f), 7);

				Mover mover;

				glm::vec3 jump_position = glm::vec3(0.0f, 0.0f, 10.0f);

				for (int j = 0; j < 25; j++)
				{

					mover.position = glm::vec3(0, 3 + 5, 10);
					mover.direction = glm::vec3(1, 0, 0);
					mover.speed = 1.0f;

					jump_position = rnd_position_around(glm::vec3(0, 20, 0), 100.0f);

					builder.jump(jump_position);
					mover.jump(jump_position);

					//mover.clear_direction();

					for (int i = 0; i < 100; i++)
					{
						mover.move();
						builder.build_to(mesh_indexed, mover.position, 1.0f + 0.5f * sinf(i * 0.001 * 3.1415 * 200.0f));
						mover.randomize_direction();
					}
				}


				//Engine_::Components_::Geometry_::Mesh_::export_to_file(mesh);
				//mesh_indexed.export_to_file();

			}
		};

		struct Tunel_Manager
		{
			std::vector<Mesh_indexed_::Mesh_indexed> meshes;
			
			std::deque<Mesh_indexed_::Mesh_indexed> q_meshes;

			Mesh_indexed_::Mesh_indexed foo_mesh;
			//Something like build_version_002 will be embeded into it.
			
			//Deque may be better than vector we remove the last one create a new one!

			const float time_between_update = 0.25f;

			float last_time_it_was_generated = 0.0f;

			bool should_generate = true;

			int cycle = 0;

			const int max_elements = 10;

			bool is_time_to_update()
			{
				return (Time_Singelton::get_total_delta_time() - last_time_it_was_generated) > time_between_update;
			}

			void update()
			{


				if (!is_time_to_update())
				{
					return;
				}


				if (q_meshes.size() < max_elements)
				{
					q_meshes.push_back(Mesh_indexed_::Mesh_indexed());
					Mesh_indexed_::Debug::add_test_quad(q_meshes.back());
					cycle += 1;
					Engine::Build_versions::build_version_002(q_meshes.back(), cycle); //now i need the new one of  this that it contine building where it stoped
					q_meshes.back().create();
				}
				else {
					q_meshes.front().free();
					q_meshes.pop_front();
				}


				//if (
				//	(Time_Singelton::get_total_delta_time() - last_time_it_was_generated) > time_between_update
				//	)
				//{
				//	last_time_it_was_generated = Time_Singelton::get_total_delta_time();
				//	std::cout << "Tunel_Manager -> ";
				//	if (should_generate)
				//	{
				//		should_generate = false;
				//		std::cout << "Building : " << cycle << std::endl;

				//		if (q_meshes.size() < max_elements)
				//		{
				//			q_meshes.push_back(Mesh_indexed_::Mesh_indexed());
				//			Mesh_indexed_::Debug::add_test_quad(q_meshes.back());
				//			cycle += 1;
				//			Engine::Build_versions::build_version_002(q_meshes.back(), cycle);
				//			q_meshes.back().create();
				//		}
				//		else {
				//			q_meshes.front().free();
				//		}

				//		Mesh_indexed_::Debug::add_test_quad(foo_mesh);
				//		Engine::Build_versions::build_version_002(foo_mesh, cycle);
				//		cycle += 1;
				//		foo_mesh.create();
				//	}
				//	else {
				//		should_generate = true;
				//		foo_mesh.free();
				//		std::cout << "Demolition" << std::endl;
				//	}
				//}

			}

			void draw()
			{
				for (int i = 0; i < q_meshes.size(); i++)
				{
					q_meshes[i].draw();
				}
			}
		};

		void map_0(Window& window)
		{

			std::cout << "window xxx" << std::endl;
			Shaders_::Shader our_shader(Constants::Shader_Default::camera_vs, Constants::Shader_Default::camera_fs);


			MeshT_::Mesh mesh;


			//Mesh Indexed
			Mesh_indexed_::Mesh_indexed mesh_indexed;
			Mesh_indexed_::Debug::add_test_quad(mesh_indexed);

			Constants::Default_Cube_Vertices::add_verts([&mesh](float x, float y, float z, float u, float v) {
				mesh.add_vertices(x, y, z, u, v);
				});

			//auto tt =  mesh.add_vertices;


			//Maps_::Map_0_::Details_::build_version_000(mesh);
			Engine::Build_versions::build_version_001(mesh);
			Engine::Build_versions::build_version_002(mesh_indexed, 0);

			mesh_indexed.create();
			mesh.create();


			Texture texture_0;
			texture_0.load_RGB(Constants::File_Paths::Images::container);

			Texture texture_1;
			texture_1.load_RGBA(Constants::File_Paths::Images::awesomeface);

			// tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
			// -------------------------------------------------------------------------------------------
			our_shader.use();
			our_shader.setInt("texture1", 0);
			our_shader.setInt("texture2", 1);

			//https://www.khronos.org/opengl/wiki/Face_Culling
			if (false) //enable faceculling
			{
				glCullFace(GL_FRONT);
				glEnable(GL_CULL_FACE);
			}

			
			Tunel_Manager tunel_man;
			//bool generate_cycle = false;
			//int cycle = 0;
			//float last_generation_time = 0.0f;
			//Mesh_indexed_::Mesh_indexed mesh_indexed_cyclic;

			// render loop
			// -----------
			while (!glfwWindowShouldClose(window.window))
			{

				
				

				// per-frame time logic
				// --------------------

				Time_Singelton::update();


				//Testing

				//if (//glfwGetKey(window.window, GLFW_KEY_G) == GLFW_PRESS 
				//	(Time_Singelton::get_total_delta_time() - last_generation_time) > 0.25f
				//	)
				//{
				//	last_generation_time = Time_Singelton::get_total_delta_time();
				//	std::cout << "Generated start";
				//	if (generate_cycle)
				//	{
				//		generate_cycle = false;
				//		std::cout << "Building : " << cycle << std::endl;
				//		Mesh_indexed_::Debug::add_test_quad(mesh_indexed_cyclic);
				//		Engine::Build_versions::build_version_002(mesh_indexed_cyclic, cycle);
				//		cycle += 1;
				//		mesh_indexed_cyclic.create();
				//	}
				//	else {
				//		generate_cycle = true;
				//		mesh_indexed_cyclic.free();
				//		std::cout << "Demolition" << std::endl;
				//	}
				//}
				tunel_man.update();


				// input
				// -----
				Engine::process_input(window.window);

				// render
				// ------
				window.clear();

				// bind textures on corresponding texture units
				texture_0.bind_to_texture_unit_0();
				texture_1.bind_to_texture_unit_1();

				// activate shader
				our_shader.use();

				// pass projection matrix to shader (note that in this case it could change every frame)
				glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)Constants::SCR_WIDTH / (float)Constants::SCR_HEIGHT, 0.1f, 100.0f);
				our_shader.setMat4("projection", projection);

				// camera/view transformation
				glm::mat4 view = camera.GetViewMatrix();
				our_shader.setMat4("view", view);

				// render boxes
				mesh.bind();//glBindVertexArray(VAO);
				for (unsigned int i = 0; i < 1; i++)
				{
					// calculate the model matrix for each object and pass it to shader before drawing
					glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
					//model = glm::translate(model, Models_data::D_000::cubePositions[i]);
					//float angle = 20.0f * i;
					//model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
					our_shader.setMat4("model", model);

					//mesh.draw();//glDrawArrays(GL_TRIANGLES, 0, mesh.vertices.size());
				}
				mesh_indexed.draw();

				tunel_man.draw();

				// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
				// -------------------------------------------------------------------------------
				glfwSwapBuffers(window.window);
				glfwPollEvents();
			}


			// optional: de-allocate all resources once they've outlived their purpose:
		// ------------------------------------------------------------------------
			mesh.free();
			mesh_indexed.free();
			our_shader.free();
			//glDeleteVertexArrays(1, &VAO);
			//glDeleteBuffers(1, &VBO);
		}
	}

	
	
	void run()
	{
		
		Window window;
		window.width = Constants::SCR_WIDTH;
		window.height = Constants::SCR_HEIGHT;
		window.init_and_configure();
		window.create();

		glfwSetFramebufferSizeCallback(window.window, Engine::framebuffer_size_callback);
		glfwSetCursorPosCallback(window.window, Engine::mouse_callback);
		glfwSetScrollCallback(window.window, Engine::scroll_callback);

		//glfwSetFramebufferSizeCallback(window, Engine::framebuffer_size_callback);
		//glfwSetCursorPosCallback(window, Engine::mouse_callback);
		//glfwSetScrollCallback(window, Engine::scroll_callback);

		//scene_0(window);
		Maps::map_0(window);

		// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
		glfwTerminate();
	}
		
}








