// OpenGL_Exploring_and_learning.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Engine.h"
#include "Mesh.h"
#include "Mesh_indexed.h"

namespace Sandbox_
{
	namespace Models_data_
	{
		namespace D_000_
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

	}

	namespace Shader_source_
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
	}

	namespace File_utils_
	{
		void todo_read_file()
		{
			// 1. retrieve the vertex/fragment source code from filePath
				//std::string vertexCode;
				//std::string fragmentCode;

				//we don't read from file
				//std::ifstream vShaderFile;
				//std::ifstream fShaderFile;
				//// ensure ifstream objects can throw exceptions:
				//vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
				//fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
				//try
				//{
				//    // open files
				//    vShaderFile.open(vertexPath);
				//    fShaderFile.open(fragmentPath);
				//    std::stringstream vShaderStream, fShaderStream;
				//    // read file's buffer contents into streams
				//    vShaderStream << vShaderFile.rdbuf();
				//    fShaderStream << fShaderFile.rdbuf();
				//    // close file handlers
				//    vShaderFile.close();
				//    fShaderFile.close();
				//    // convert stream into string
				//    vertexCode = vShaderStream.str();
				//    fragmentCode = fShaderStream.str();
				//}
				//catch (std::ifstream::failure& e)
				//{
				//    std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ: " << e.what() << std::endl;
				//}

				//const char* vShaderCode = vertexCode.c_str();
				//const char* fShaderCode = fragmentCode.c_str();
		}

	}

	namespace Shaders_
	{
		class Shader
		{
		public:
			unsigned int ID;
			// constructor generates the shader on the fly
			// ------------------------------------------------------------------------
			Shader(const char* vShaderCode, const char* fShaderCode)//(const char* vertexPath, const char* fragmentPath)
			{



				// 2. compile shaders
				unsigned int vertex, fragment;
				// vertex shader
				vertex = glCreateShader(GL_VERTEX_SHADER);
				glShaderSource(vertex, 1, &vShaderCode, NULL);
				glCompileShader(vertex);
				checkCompileErrors(vertex, "VERTEX");
				// fragment Shader
				fragment = glCreateShader(GL_FRAGMENT_SHADER);
				glShaderSource(fragment, 1, &fShaderCode, NULL);
				glCompileShader(fragment);
				checkCompileErrors(fragment, "FRAGMENT");
				// shader Program
				ID = glCreateProgram();
				glAttachShader(ID, vertex);
				glAttachShader(ID, fragment);
				glLinkProgram(ID);
				checkCompileErrors(ID, "PROGRAM");
				// delete the shaders as they're linked into our program now and no longer necessery
				glDeleteShader(vertex);
				glDeleteShader(fragment);

			}

			void free()
			{
				glDeleteProgram(ID);
			}

			// activate the shader
			// ------------------------------------------------------------------------
			void use() const
			{
				glUseProgram(ID);
			}
			// utility uniform functions
			// ------------------------------------------------------------------------
			void setBool(const std::string& name, bool value) const
			{
				glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
			}
			// ------------------------------------------------------------------------
			void setInt(const std::string& name, int value) const
			{
				glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
			}
			// ------------------------------------------------------------------------
			void setFloat(const std::string& name, float value) const
			{
				glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
			}
			// ------------------------------------------------------------------------
			void setVec2(const std::string& name, const glm::vec2& value) const
			{
				glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
			}
			void setVec2(const std::string& name, float x, float y) const
			{
				glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y);
			}
			// ------------------------------------------------------------------------
			void setVec3(const std::string& name, const glm::vec3& value) const
			{
				glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
			}
			void setVec3(const std::string& name, float x, float y, float z) const
			{
				glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
			}
			// ------------------------------------------------------------------------
			void setVec4(const std::string& name, const glm::vec4& value) const
			{
				glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
			}
			void setVec4(const std::string& name, float x, float y, float z, float w) const
			{
				glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w);
			}
			// ------------------------------------------------------------------------
			void setMat2(const std::string& name, const glm::mat2& mat) const
			{
				glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
			}
			// ------------------------------------------------------------------------
			void setMat3(const std::string& name, const glm::mat3& mat) const
			{
				glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
			}
			// ------------------------------------------------------------------------
			void setMat4(const std::string& name, const glm::mat4& mat) const
			{
				glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
			}

		private:
			// utility function for checking shader compilation/linking errors.
			// ------------------------------------------------------------------------
			void checkCompileErrors(GLuint shader, std::string type)
			{
				GLint success;
				GLchar infoLog[1024];
				if (type != "PROGRAM")
				{
					glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
					if (!success)
					{
						glGetShaderInfoLog(shader, 1024, NULL, infoLog);
						std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
					}
				}
				else
				{
					glGetProgramiv(shader, GL_LINK_STATUS, &success);
					if (!success)
					{
						glGetProgramInfoLog(shader, 1024, NULL, infoLog);
						std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
					}
				}
			}
		};
	}

	namespace Cam_
	{
		// Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods
		enum Camera_Movement {
			FORWARD,
			BACKWARD,
			LEFT,
			RIGHT
		};

		// Default camera values
		const float YAW = -90.0f;
		const float PITCH = 0.0f;
		const float SPEED = 2.5f;
		const float SENSITIVITY = 0.1f;
		const float ZOOM = 45.0f;

		class Camera
		{
		public:
			// camera Attributes
			glm::vec3 Position;
			glm::vec3 Front;
			glm::vec3 Up;
			glm::vec3 Right;
			glm::vec3 WorldUp;
			// euler Angles
			float Yaw;
			float Pitch;
			// camera options
			float MovementSpeed;
			float MouseSensitivity;
			float Zoom;

			// constructor with vectors
			Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
			{
				Position = position;
				WorldUp = up;
				Yaw = yaw;
				Pitch = pitch;
				updateCameraVectors();
			}
			// constructor with scalar values
			Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
			{
				Position = glm::vec3(posX, posY, posZ);
				WorldUp = glm::vec3(upX, upY, upZ);
				Yaw = yaw;
				Pitch = pitch;
				updateCameraVectors();
			}

			// returns the view matrix calculated using Euler Angles and the LookAt Matrix
			glm::mat4 GetViewMatrix()
			{
				return glm::lookAt(Position, Position + Front, Up);
			}

			// processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
			void ProcessKeyboard(Camera_Movement direction, float deltaTime)
			{
				float velocity = MovementSpeed * deltaTime;
				if (direction == FORWARD)
					Position += Front * velocity;
				if (direction == BACKWARD)
					Position -= Front * velocity;
				if (direction == LEFT)
					Position -= Right * velocity;
				if (direction == RIGHT)
					Position += Right * velocity;
			}

			// processes input received from a mouse input system. Expects the offset value in both the x and y direction.
			void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true)
			{
				xoffset *= MouseSensitivity;
				yoffset *= MouseSensitivity;

				Yaw += xoffset;
				Pitch += yoffset;

				// make sure that when pitch is out of bounds, screen doesn't get flipped
				if (constrainPitch)
				{
					if (Pitch > 89.0f)
						Pitch = 89.0f;
					if (Pitch < -89.0f)
						Pitch = -89.0f;
				}

				// update Front, Right and Up Vectors using the updated Euler angles
				updateCameraVectors();
			}

			// processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
			void ProcessMouseScroll(float yoffset)
			{
				Zoom -= (float)yoffset;
				if (Zoom < 1.0f)
					Zoom = 1.0f;
				if (Zoom > 45.0f)
					Zoom = 45.0f;
			}

		private:
			// calculates the front vector from the Camera's (updated) Euler Angles
			void updateCameraVectors()
			{
				// calculate the new Front vector
				glm::vec3 front;
				front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
				front.y = sin(glm::radians(Pitch));
				front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
				Front = glm::normalize(front);
				// also re-calculate the Right and Up vector
				Right = glm::normalize(glm::cross(Front, WorldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
				Up = glm::normalize(glm::cross(Right, Front));
			}
		};
	}


	void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	void mouse_callback(GLFWwindow* window, double xpos, double ypos);
	void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
	void process_input(GLFWwindow* window);

	// settings
	const unsigned int SCR_WIDTH = 1980;//800;
	const unsigned int SCR_HEIGHT = 1080;//600;

	// camera
	Cam_::Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
	float lastX = SCR_WIDTH / 2.0f;
	float lastY = SCR_HEIGHT / 2.0f;
	bool firstMouse = true;

	// timing
	float deltaTime = 0.0f;	// time between current frame and last frame
	float lastFrame = 0.0f;



	// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
	void process_input(GLFWwindow* window)
	{
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, true);

		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			camera.ProcessKeyboard(Cam_::Camera_Movement::FORWARD, deltaTime);
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			camera.ProcessKeyboard(Cam_::Camera_Movement::BACKWARD, deltaTime);
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			camera.ProcessKeyboard(Cam_::Camera_Movement::LEFT, deltaTime);
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			camera.ProcessKeyboard(Cam_::Camera_Movement::RIGHT, deltaTime);
	}

	// glfw: whenever the window size changed (by OS or user resize) this callback function executes
	// ---------------------------------------------------------------------------------------------
	void framebuffer_size_callback(GLFWwindow* window, int width, int height)
	{
		std::cout << "Window width : " << width << " height : " << height << std::endl;
		// make sure the viewport matches the new window dimensions; note that width and 
		// height will be significantly larger than specified on retina displays.
		glViewport(0, 0, width, height);
	}


	// glfw: whenever the mouse moves, this callback is called
	// -------------------------------------------------------
	void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
	{
		float xpos = static_cast<float>(xposIn);
		float ypos = static_cast<float>(yposIn);

		if (firstMouse)
		{
			lastX = xpos;
			lastY = ypos;
			firstMouse = false;
		}

		float xoffset = xpos - lastX;
		float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

		lastX = xpos;
		lastY = ypos;

		camera.ProcessMouseMovement(xoffset, yoffset);
	}

	// glfw: whenever the mouse scroll wheel scrolls, this callback is called
	// ----------------------------------------------------------------------
	void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
	{
		camera.ProcessMouseScroll(static_cast<float>(yoffset));
	}

	namespace Win_
	{
		struct Window
		{
			int width;
			int height;
			GLFWwindow* window;

			void init_and_configure()
			{
				//glfw: initialize and configure
				// ------------------------------
				glfwInit();
				glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
				glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
				glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
			}

			void create()
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
				glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
				glfwSetCursorPosCallback(window, mouse_callback);
				glfwSetScrollCallback(window, scroll_callback);


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

			void capture_mouse()
			{
				// tell GLFW to capture our mouse
				glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			}

			void clear()
			{
				glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			}

		};




	}

	//Engine
	// Texture system
	// Gameobject System
	//  Game object
	// Entetry System
	//  Shaders System
	//  Mesh System
	//  Transform
	//  

	namespace Engine_
	{

		namespace Components_
		{
			struct Transform
			{
				glm::vec3 position;
				glm::vec3 rotation;
				glm::vec3 scale;
			};

			



			// TODO
		   // -> exporter obj for mesh
		   // -> refactur
			namespace Geometry_
			{

				

				








				namespace Tunel_Builder_
				{

					struct Tunel_Builder
					{
						glm::vec3 current_pos;

						std::vector<glm::vec3> ring_previus;
						std::vector<glm::vec3> ring_next;

						bool first_time;
						int number_section;
						Tunel_Builder(glm::vec3 pos, int set_number_section)
						{
							current_pos = pos;
							first_time = true;
							number_section = set_number_section;
						}

						void jump(glm::vec3 pos)
						{
							current_pos = pos;
							first_time = true;
							ring_previus.clear();
							ring_next.clear();
						}

						void build_to(Mesh_indexed_::Mesh_indexed& mesh_indexed, glm::vec3 next, float radius)
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

						void build_to(MeshT_::Mesh& mesh, glm::vec3 next, float radius)
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


					};


				}







				//--
			}





		}



	}

	namespace Maps_
	{
		namespace Map_0_
		{
			namespace Details_
			{
				struct Mover
				{
					glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
					glm::vec3 direction = glm::vec3(1.0f, 0.0f, 0.0f);
					float speed = 1.0f;

					void move()
					{
						position += direction * speed;
					}


					void randomize_direction()
					{
						float dx = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
						float dy = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
						float dz = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
						direction += glm::vec3(dx - 0.5f, dy - 0.5f, dz - 0.5f) * 0.25f;

						direction = glm::normalize(direction);
					}

					void jump(glm::vec3 pos)
					{
						position = pos;
					}

					void clear_direction()
					{
						direction = glm::vec3(0.0f, 0.0f, 0.0f);
					}
				};

				
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

						//direction *= 0.25f;
						//direction *= 0.15f;
						//build_section(mesh, s_a, s_b, 0.5f, 0.2f);
						MeshT_::build_section(mesh, s_a, s_b, 1.0f, 1.0f);
					}

					//build_section(mesh, glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 1.0));
					//build_section(mesh, glm::vec3(0.0, 1.0, 1.0), glm::vec3(0.0, -2.0, -5.0));


				}

				//--
				void build_version_001(MeshT_::Mesh& mesh)
				{
					mesh.vertices.clear();
					//Engine_::Components_::Geometry_::Mesh_::scale(mesh, 0.1f);








					Engine_::Components_::Geometry_::Tunel_Builder_::Tunel_Builder builder(glm::vec3(0.0f, 0.0f, 0.0f), 7);

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

				void build_version_002(Mesh_indexed_::Mesh_indexed& mesh_indexed)
				{
					auto rnd_position_around = [](glm::vec3 center, float radius)
					{
						float x = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
						float y = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
						float z = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
						return glm::vec3(x - 0.5f, y - 0.5f, z - 0.5f) * radius;
					};

					//mesh_indexed.clear();

					Engine_::Components_::Geometry_::Tunel_Builder_::Tunel_Builder builder(glm::vec3(0.0f, 0.0f, 0.0f), 7);

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


			void map_0(Win_::Window& window)
			{
				Shaders_::Shader our_shader(Shader_source_::camera_vs, Shader_source_::camera_fs);

				MeshT_::Mesh mesh;


				//Mesh Indexed
				Mesh_indexed_::Mesh_indexed mesh_indexed;
				Mesh_indexed_::Debug::add_test_quad(mesh_indexed);




				/*for (int i = 0; i < 10; i++)
				{
					Engine_::Components_::Geometry_::Mesh_indexed_::add_quad(
						mesh_indexed,
						glm::vec3(0 + 20 * i, 0, 0),
						glm::vec3(0 + 20 * i, 20, 0),
						glm::vec3(20 + 20 * i, 20, 0),
						glm::vec3(20 + 20 * i, 0, 0)
					);

				}*/



				for (int i = 0; i < 36; i++)
				{
					float x = Models_data_::D_000_::vertices[i * 5 + 0];//x
					float y = Models_data_::D_000_::vertices[i * 5 + 1];//y
					float z = Models_data_::D_000_::vertices[i * 5 + 2];//z

					float u = Models_data_::D_000_::vertices[i * 5 + 3];//u
					float v = Models_data_::D_000_::vertices[i * 5 + 4];//v
					mesh.add_vertices(x, y, z, u, v);
				}

				//Maps_::Map_0_::Details_::build_version_000(mesh);
				Maps_::Map_0_::Details_::build_version_001(mesh);
				Maps_::Map_0_::Details_::build_version_002(mesh_indexed);

				mesh_indexed.create();
				mesh.create();


				Engine::Texture texture_0;
				const char* path_0 = "Textures/container.jpg";
				texture_0.load_RGB(path_0);

				Engine::Texture texture_1;
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
					float currentFrame = static_cast<float>(glfwGetTime());
					deltaTime = currentFrame - lastFrame;
					lastFrame = currentFrame;

					// input
					// -----
					process_input(window.window);

					// render
					// ------
					window.clear();

					// bind textures on corresponding texture units
					texture_0.bind_to_texture_unit_0();
					texture_1.bind_to_texture_unit_1();

					// activate shader
					our_shader.use();

					// pass projection matrix to shader (note that in this case it could change every frame)
					glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
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
		Win_::Window window;
		window.width = SCR_WIDTH;
		window.height = SCR_HEIGHT;
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
