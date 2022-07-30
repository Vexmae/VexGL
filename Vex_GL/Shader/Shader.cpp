#include "Shader.h"

//Creates a shader program with the shader path given as argument.
unsigned int VexGL::Shader::Shader::LoadShader() {

	const char* VertexSource = 
#include "VertexSource/BaseVertex.vs"
		;

	const char* FragmentSource =
#include "FragmentSource/BaseFrag.vs"
		;


	unsigned int ShaderProgram = glCreateProgram();
	unsigned int VertexShader = glCreateShader(GL_VERTEX_SHADER);
	unsigned int FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(VertexShader, 1,&VertexSource, NULL);
	glShaderSource(FragmentShader, 1, &FragmentSource, NULL);


	int status;
	char infolog[512];

	glCompileShader(VertexShader);
	glGetShaderiv(VertexShader, GL_COMPILE_STATUS, &status);
	glGetShaderInfoLog(VertexShader, 512, NULL, infolog);
	if (status == 0) { std::cout << "Vertex shader compilation failed: " << infolog << std::endl; }

	glCompileShader(FragmentShader);
	glGetShaderiv(FragmentShader, GL_COMPILE_STATUS, &status);
	glGetShaderInfoLog(FragmentShader, 512, NULL, infolog);
	if (status == 0) { std::cout << "Fragment shader compilation failed: " << infolog << std::endl; }

	glAttachShader(ShaderProgram, VertexShader);
	glAttachShader(ShaderProgram, FragmentShader);
	
	glLinkProgram(ShaderProgram);
	glGetProgramiv(ShaderProgram, GL_LINK_STATUS, &status);
	glGetProgramInfoLog(ShaderProgram, 512, NULL, infolog);
	if (status == 0) { std::cout << "Shader program link failed: " << infolog << std::endl; }

	glDeleteShader(VertexShader);
	glDeleteShader(FragmentShader);

	return ShaderProgram;
}
