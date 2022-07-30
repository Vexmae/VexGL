#include "vglShader.h"

vglShader::vglShader(int vertexID, int fragmentID) {
	//this here is a bit ugly, i'm sorry for this.

	_shaderProgram = glCreateProgram();
	_vertexShader = glCreateShader(GL_VERTEX_SHADER);
	_fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	std::string vertexSource;
	vglGetVertexSource(vertexID, &vertexSource);
	const char* _vertexSource = vertexSource.c_str();
	glShaderSource(_vertexShader, 1, &_vertexSource, NULL);
	glCompileShader(_vertexShader);

	int succes;
	char infolog[512];
	glGetShaderiv(_vertexShader, GL_COMPILE_STATUS, &succes);
	glGetShaderInfoLog(_vertexShader, 512, NULL, infolog);
	if (!succes) { std::cout << "Vertex Shader (ID: " << vertexID << ") failed to compile: " << infolog << std::endl; };

	std::string fragmentSource;
	vglGetFragmentSource(fragmentID, &fragmentSource);
	const char* _fragmentSource = fragmentSource.c_str();
	glShaderSource(_fragmentShader, 1, &_fragmentSource, NULL);
	glCompileShader(_fragmentShader);

	glGetShaderiv(_fragmentShader, GL_COMPILE_STATUS, &succes);
	glGetShaderInfoLog(_fragmentShader, 512, NULL, infolog);
	if (!succes) { std::cout << "Fragment Shader (ID: " << vertexID << ") failed to compile: " << infolog << std::endl; };

	glAttachShader(_shaderProgram, _vertexShader);
	glAttachShader(_shaderProgram, _fragmentShader);
	glLinkProgram(_shaderProgram);


	glGetProgramiv(_shaderProgram, GL_LINK_STATUS, &succes);
	glGetProgramInfoLog(_shaderProgram, 512, NULL, infolog);
	if (!succes) { std::cout << "Failed to link shader program: " << infolog << std::endl; };

	glDeleteShader(_vertexShader);
	glDeleteShader(_fragmentShader);
}

void vglShader::vglGetShaderID(unsigned int* shaderProgram) {
	*shaderProgram = _shaderProgram;
}

void vglShader::Use() {
	glUseProgram(_shaderProgram);
}

void vglShader::Delete() {
	glDeleteProgram(_shaderProgram);
}

//this code is a mess
void vglShader::vglGetVertexSource(int vertexID, std::string* vertexSource) {
	switch (vertexID) {
		case VGL_VERTEX_DEFAULT:
			const char* x =
#include "Vertex/defaultVertex.glsl"
				; *vertexSource = std::string(x); return;
	}
}

void vglShader::vglGetFragmentSource(int fragmentID, std::string* fragmentSource) {
	switch (fragmentID) {
		case VGL_FRAGMENT_DEFAULT:
			const char* x =
#include "Fragment/defaultFragment.glsl"
				; *fragmentSource = std::string(x); return;
	}
}
