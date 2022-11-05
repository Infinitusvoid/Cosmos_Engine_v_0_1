// OpenGL_Exploring_and_learning.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include "Game.h"




namespace Sandbox_
{
	
	

	
	namespace Maps_
	{
		namespace Map_0_
		{
			


			void map_0(Game::Win_::Window& window)
			{
				
				
				Shaders_::Shader our_shader = Game::Shader_source_::create_shader();

				MeshT_::Mesh mesh;


				//Mesh Indexed
				Mesh_indexed_::Mesh_indexed mesh_indexed;
				Mesh_indexed_::Debug::add_test_quad(mesh_indexed);

				Game::Models_data_::D_000_::add_verts([&mesh](float x, float y, float z, float u, float v) {
					mesh.add_vertices(x, y, z, u, v);
					});

				//auto tt =  mesh.add_vertices;


				//Maps_::Map_0_::Details_::build_version_000(mesh);
				Game::Build_versions::build_version_001(mesh);
				Game::Build_versions::build_version_002(mesh_indexed);

				mesh_indexed.create();
				mesh.create();


				Texture texture_0;
				const char* path_0 = "Textures/container.jpg";
				texture_0.load_RGB(path_0);

				Texture texture_1;
				const char* path_1 = "Textures/awesomeface.png";
				texture_1.load_RGBA(path_1);

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


				// render loop
				// -----------
				while (!glfwWindowShouldClose(window.window))
				{
					// per-frame time logic
					// --------------------
					
					Game::Time_calc::update();
					

					// input
					// -----
					Game::process_input(window.window);

					// render
					// ------
					window.clear();

					// bind textures on corresponding texture units
					texture_0.bind_to_texture_unit_0();
					texture_1.bind_to_texture_unit_1();

					// activate shader
					our_shader.use();

					// pass projection matrix to shader (note that in this case it could change every frame)
					glm::mat4 projection = glm::perspective(glm::radians((*Game::get_cam()).Zoom), (float)Game::SCR_WIDTH / (float)Game::SCR_HEIGHT, 0.1f, 100.0f);
					our_shader.setMat4("projection", projection);

					// camera/view transformation
					glm::mat4 view = (*Game::get_cam()).GetViewMatrix();
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

	}


	void run()
	{
		Game::Win_::Window window;
		window.width = Game::SCR_WIDTH;
		window.height = Game::SCR_HEIGHT;
		window.init_and_configure();
		window.create();

		//scene_0(window);
		Maps_::Map_0_::map_0(window);
		// glfw: terminate, clearing all previously allocated GLFW resources.
		// ------------------------------------------------------------------
		glfwTerminate();
	}


}

int main()
{
	Sandbox_::run();
}
