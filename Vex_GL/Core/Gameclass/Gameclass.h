#pragma once
#include <glad/glad.h>
#include <iostream>
#include <glfw3.h>
#include "../Loop/Loop.h"
#include "../../Shader/Shader.h"
#include "../../FileLoader/TextureLoader.h"
#include <string.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stb_image.h>

namespace VexGL {
	namespace Core {
		class Gameclass : public Loop {

			public:
				void Run();
				double DeltaTime;
				double LastFrame;

				static float camPitch;
				static float camYaw;
			private:
				void Initialize();
				void Load();
				void Render();
				void Update();
				static void KeyCallBack(GLFWwindow* window, int key, int scancode, int action, int mods);
				static void mouse_callback(GLFWwindow* window, double xpos, double ypos);

				unsigned int VBO = 0;
				unsigned int VAO = 0;
				unsigned int EBO = 0;
				unsigned int texture0 = 0;
				unsigned int texture1 = 0;

				static int Direction;
				static float Opacity;
				static float Xoffset;
				static float Yoffset;
				static float Rotation;
				static float Scale;
				static bool iswireframe;

				int WindowWidth = 0;
				int WindowHeight = 0;

				unsigned int shaderProgram = 0;

				//transition variable
				static glm::mat4 trans;
				static glm::mat4 projection;
				static glm::mat4 model;
				static glm::mat4 view;

				float camX = 0.0f;
				float camZ = 3.0f;
				float camY = 0.0f;

				glm::vec3 direction;

				glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
				glm::vec3 cameraPosition = glm::vec3(0.0f, 0.0f, 3.0f);
				glm::vec3 cameraDirection = glm::normalize(cameraPosition - cameraTarget);

				glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
				glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
				glm::vec3 cameraRight = glm::vec3(glm::cross(up, cameraDirection));
				glm::vec3 cameraUp = glm::vec3(glm::cross(cameraDirection, cameraRight));

				float verticies[10000] = {
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

				unsigned int indices[7]{
					0,1,2, //triangle 1
					0,2,3 //triangle 2 
				};


				float texCoords[50] = {
					0.0f, 0.0f,  // lower-left corner  
					1.0f, 0.0f,  // lower-right corner
					0.5f, 1.0f   // top-center corner
				};
		};
	}
}