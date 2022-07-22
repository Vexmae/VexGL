#pragma once
#include <glad/glad.h>
#include "glfw3.h"
#include <iostream>

namespace VexGL {
	namespace Core {
		namespace DisplayManager {
			void CreateWindow(int Width, int Height, char Title[30]);
			void DestroyWindow();
		};
	}
}

