#pragma once
#include <glad/glad.h>
#include "../DisplayManager/DisplayManager.h"

namespace VexGL {
	namespace Core {
		class Loop {
			public:
				int FrameSinceStart;
				void Run() {
					Initialize();

					char Title[30] = "Hello World";
					VexGL::Core::DisplayManager::CreateWindow(500,500,Title);
					FrameSinceStart = 0;

					Load();

					while (!glfwWindowShouldClose(glfwGetCurrentContext())) {
						Render();
						glfwPollEvents();
						Update();
					}

					VexGL::Core::DisplayManager::DestroyWindow();
				}
			protected:
				//Executes at the very start of the script
				virtual void Initialize(){}
				//Executes before the first frame is rendered
				virtual void Load(){}
				//Executes with every frame renderer
				virtual void Render(){}
				//Executes after every frame
				virtual void Update() {
				}
		};
	}
}

