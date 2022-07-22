#include "DisplayManager.h"

void VexGL::Core::DisplayManager::CreateWindow(int Width, int Height, char Title[30]) {
	
	
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, true);
	glfwWindowHint(GLFW_FOCUSED, true);

	GLFWwindow* window = glfwCreateWindow(Width, Height, Title, NULL, NULL);

	if (!window) { throw std::runtime_error("Window Creation Failed"); }

	glfwMakeContextCurrent(window);
	gladLoadGL();

	glViewport(10, 10, Width, Height);

	glfwSwapInterval(1); //V-sync on with 1, off with 0. 
}

void VexGL::Core::DisplayManager::DestroyWindow() {
	glfwTerminate();
}
