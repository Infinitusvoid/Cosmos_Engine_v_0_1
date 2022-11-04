#include "Game.h"

namespace Game
{

	// set up vertex data (and buffer(s)) and configure vertex attributes
			// ------------------------------------------------------------------
	float vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};
	// world space positions of our cubes
	glm::vec3 cubePositions[] = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};

}

void Game::Models_data_::D_000_::add_verts(std::function<void(float, float, float, float, float)> f)
{
	
	for (int i = 0; i < 36; i++)
	{
		float x = vertices[i * 5 + 0];//x
		float y = vertices[i * 5 + 1];//y
		float z = vertices[i * 5 + 2];//z

		float u = vertices[i * 5 + 3];//u
		float v = vertices[i * 5 + 4];//v
		f(x, y, z, u, y);
	}
}

Shaders_::Shader Game::Shader_source_::create_shader()
{
	const char* camera_fs = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"\n"
		"in vec2 TexCoord;\n"
		"\n"
		"uniform sampler2D texture1;\n"
		"uniform sampler2D texture2;\n"
		"\n"
		"void main()\n"
		"{\n"
		"FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.2);\n"
		"}\n";


	const char* camera_vs = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"layout (location = 1) in vec2 aTexCoord;\n"
		"\n"
		"out vec2 TexCoord;\n"
		"\n"
		"uniform mat4 model;\n"
		"uniform mat4 view;\n"
		"uniform mat4 projection;\n"
		"\n"
		"void main()\n"
		"{\n"
		" gl_Position = projection * view * model * vec4(aPos, 1.0f);\n"
		" TexCoord = vec2(aTexCoord.x, aTexCoord.y);\n"
		"}\n";

	Shaders_::Shader our_shader(camera_vs, camera_fs);
	return our_shader;
}

namespace Game::Time_calc
{
	// timing
	float deltaTime = 0.0f;	// time between current frame and last frame
	float lastFrame = 0.0f;

	void update()
	{
		float currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
	}

	float get_delta_time()
	{
		return deltaTime;
	}
}

namespace Game::Last_mouse_XY
{
	float lastX = Game::SCR_WIDTH / 2.0f;
	float lastY = Game::SCR_HEIGHT / 2.0f;
	bool firstMouse = true;

	float xoffset = 0.0f;
	float yoffset = 0.0f;

	void update(double xposIn, double yposIn)
	{
		float xpos = static_cast<float>(xposIn);
		float ypos = static_cast<float>(yposIn);

		if (firstMouse)
		{
			lastX = xpos;
			lastY = ypos;
			firstMouse = false;
		}

		xoffset = xpos - lastX;
		yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

		lastX = xpos;
		lastY = ypos;
	}

	float get_x_offset()
	{
		return xoffset;
	}

	float get_y_offset()
	{
		return yoffset;
	}

}

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
