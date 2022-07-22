#pragma once
#include <glad/glad.h>
#include <iostream>
#include <glfw3.h>
#include "../Loop/Loop.h"
#include "../../Shader/Shader.h"

#include <stb_image.h>

namespace VexGL {
	namespace Core {
		class Gameclass : public Loop {

			public:
				void Run();
				double DeltaTime;
				double LastFrame;
			private:
				void Initialize();
				void Load();
				void Render();
				void Update();
				static void KeyCallBack(GLFWwindow* window, int key, int scancode, int action, int mods);

				unsigned int VBO = 0;
				unsigned int VAO = 0;
				unsigned int EBO = 0;
				unsigned int texture0 = 0;
				unsigned int texture1 = 0;

				static int Direction;
				static float Opacity;
				static float Xoffset;
				static float Yoffset;
				static bool iswireframe;

				unsigned int shaderProgram = 0;

				float verticies[512] = {
					// positions          // colors           // texture coords
					 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
					 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
					-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
					-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
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