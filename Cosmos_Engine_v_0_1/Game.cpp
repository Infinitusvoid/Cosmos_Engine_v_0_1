#include "Game.h"





void Game::Build_versions::build_version_000(MeshT_::Mesh& mesh)
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

		//direction *= 0.25f;
		//direction *= 0.15f;
		//build_section(mesh, s_a, s_b, 0.5f, 0.2f);
		MeshT_::build_section(mesh, s_a, s_b, 1.0f, 1.0f);
	}

	//build_section(mesh, glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 1.0));
	//build_section(mesh, glm::vec3(0.0, 1.0, 1.0), glm::vec3(0.0, -2.0, -5.0));


}

void Game::Build_versions::build_version_001(MeshT_::Mesh& mesh)
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

void Game::Build_versions::build_version_002(Mesh_indexed_::Mesh_indexed& mesh_indexed)
{
	auto rnd_position_around = [](glm::vec3 center, float radius)
	{
		float x = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		float y = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		float z = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		return glm::vec3(x - 0.5f, y - 0.5f, z - 0.5f) * radius;
	};

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

void Game::Win_::Window::init_and_configure()
{
	//glfw: initialize and configure
	// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void Game::Win_::Window::create()
{
	// glfw window creation
	// --------------------
	window = glfwCreateWindow(width, height, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return;
	}
	glfwMakeContextCurrent(window);




	//Set callbacks
	glfwSetFramebufferSizeCallback(window, Engine::framebuffer_size_callback);
	glfwSetCursorPosCallback(window, Engine::mouse_callback);
	glfwSetScrollCallback(window, Engine::scroll_callback);


	capture_mouse();

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return;
	}

	// configure global opengl state
	// -----------------------------
	glEnable(GL_DEPTH_TEST);
}

void Game::Win_::Window::capture_mouse()
{
	// tell GLFW to capture our mouse
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Game::Win_::Window::clear()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Game::Maps_::Map_0_::map_0(Game::Win_::Window& window)
{


	Shaders_::Shader our_shader = Engine::Shader_source_::create_shader();

	MeshT_::Mesh mesh;


	//Mesh Indexed
	Mesh_indexed_::Mesh_indexed mesh_indexed;
	Mesh_indexed_::Debug::add_test_quad(mesh_indexed);

	Engine::Models_data_::add_verts([&mesh](float x, float y, float z, float u, float v) {
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

		Engine::Time_calc::update();


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
		glm::mat4 projection = glm::perspective(glm::radians((*Engine::get_cam()).Zoom), (float)Engine::SCR_WIDTH / (float)Engine::SCR_HEIGHT, 0.1f, 100.0f);
		our_shader.setMat4("projection", projection);

		// camera/view transformation
		glm::mat4 view = (*Engine::get_cam()).GetViewMatrix();
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

void Game::Sandbox_::run()
{
	Game::Win_::Window window;
	window.width = Engine::SCR_WIDTH;
	window.height = Engine::SCR_HEIGHT;
	window.init_and_configure();
	window.create();

	//scene_0(window);
	Game::Maps_::Map_0_::map_0(window);
	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
}
