#pragma once
#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <iostream>
#include <string>

#include "Graphics/Shader/vglShader.h"
#include "Objects/Cube/vglCube.h"
#include "Functions/Time/vglTime.h"

GLFWwindow* window;
vglCube cube;
vglCube cube2;

bool iswireframe = false;

const int START_WIDTH = 600;
const int START_HEIGHT = 600;
char START_TITLE[] = "VexGL";

unsigned int VAO, VBO, EBO;
unsigned int ShaderProgram;

int main();
int WinMain();

void Run();
void Initialize();
void Load();
void Render();
void Update();

void vglAssignCallbacks();

void vglViewportSizeCallback(GLFWwindow* window, int width, int height);
void vglKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

void vglCreateWindow(int width, int height, char title[], bool fullscreen);
