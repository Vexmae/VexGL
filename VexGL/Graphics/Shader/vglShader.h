#pragma once
#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <iostream>

#define VGL_VERTEX_DEFAULT 0
#define VGL_FRAGMENT_DEFAULT 0

class vglShader {
	public:
		vglShader(int vertexID, int fragmentID);
		void vglGetShaderID(unsigned int* shaderProgram);
		
		void Use();
		void Delete();
	private:
		void vglGetVertexSource(int vertexID, std::string* vertexSource);
		void vglGetFragmentSource(int fragmentID, std::string* fragmentSource);
		unsigned int _shaderProgram = 0;
		unsigned int _vertexShader = 0;
		unsigned int _fragmentShader = 0;
};

