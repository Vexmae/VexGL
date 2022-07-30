#include "Gameclass.h"
#include <Windows.h>

float VexGL::Core::Gameclass::Xoffset;
float VexGL::Core::Gameclass::Yoffset;
float VexGL::Core::Gameclass::Opacity;
float VexGL::Core::Gameclass::Rotation;
float VexGL::Core::Gameclass::Scale;
glm::mat4 VexGL::Core::Gameclass::trans;
int VexGL::Core::Gameclass::Direction;
bool VexGL::Core::Gameclass::iswireframe;

glm::mat4 VexGL::Core::Gameclass::model;
glm::mat4 VexGL::Core::Gameclass::projection;
glm::mat4 VexGL::Core::Gameclass::view;

void VexGL::Core::Gameclass::Run() {
	Loop::Run();
}

void VexGL::Core::Gameclass::Initialize() {

}

void VexGL::Core::Gameclass::Load() {

	shaderProgram = VexGL::Shader::Shader::LoadShader();
	glUseProgram(shaderProgram); 


	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	//GPU Buffer to copy to, size of the data in bytes, vertex data, use of the data.
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_DYNAMIC_DRAW);

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_DYNAMIC_DRAW);

	//Position Attributes
	glVertexAttribPointer(0,3,GL_FLOAT,false,5*sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//Color Attributes
	//Le premier chiffre correspond au layout location du shader vertex, le nombre de valeur de notre info (ici 3 pour RGB), le type des valeurs, false, 
	//la taille en mémoire de chaque vertex, le offset en mémoire du début des valeurs (ici 3 fois la taille d'un float (qui correspond à passer les 3 première valeurs de position))
	//glVertexAttribPointer(1, 3, GL_FLOAT, false, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	//glEnableVertexAttribArray(1); //On active l'attrib pointer 1

	glVertexAttribPointer(2, 2, GL_FLOAT, false, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(2);

	//Défini comment les texture doivent se comporter quand elles ne peuvent pas remplir un objet.
	//La cible (ici on travaille avec des textures 2d), le paramètre (ici WRAP_S qui correspond au wrap sur l'axe S similaire à l'axe X), La valeur (ici on fait se répéter la texture.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	//Les coordonnéees de textures ne dépendent pas de la résolution de l'image, OpenGL doit donc décider quelles pixel d'image associer à quelle coordonée.
	//Pour faire ceci il existe le mode NEAREST qui prend simplement en compte le pixel pile sous la coordonée
	//il y a aussi le mode LINEAR qui fait une moyenne de la couleur de tout les pixels alentours.
	//c'est du Texture Filtering et il peut être défini indépendament pour l'aggrandissement et le rétrécissement d'une texture.

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	char buffer[MAX_PATH]={};
	GetModuleFileNameA(NULL, buffer, MAX_PATH);
	std::string::size_type pos = std::string(buffer).find_last_of("\\/");

	std::string path = std::string(buffer).substr(0, pos);

	int Width, Height, ColorChannelNbr;
	texture0 = VexGL::TextureLoader::CreateTexture2DFromFile(path + "/container.jpg", &Width, &Height, &ColorChannelNbr, GL_RGB, false, GL_TEXTURE0);
	texture1 = VexGL::TextureLoader::CreateTexture2DFromFile(path + "/megaman.png", &Width, &Height, &ColorChannelNbr, GL_RGBA, true, GL_TEXTURE1);

	//Now we tell openGL which texture is which
	//On dit que l'uniform "Texture0" est égal à GL_TEXTURE0 ((on écrit juste 0))
	glUniform1i(glGetUniformLocation(shaderProgram, "Texture0"), 0);
	glUniform1i(glGetUniformLocation(shaderProgram, "Texture1"), 1);

	Direction = 1;
	Opacity = 0.5;
	Scale = 0.5;
	iswireframe = false;
	glfwSetKeyCallback(glfwGetCurrentContext(), KeyCallBack );

	int windowW, windowH;
	glfwGetWindowSize(glfwGetCurrentContext(), &windowW, &windowH);

	//FOV, Format of the projection, near plane, far plane
	projection = glm::perspective(glm::radians(45.0f), (float)windowW / (float)windowH, 0.1f, 100.0f);

	model = glm::mat4(1.0f);

	// note that we're translating the scene in the reverse direction of where we want to move

	
	//model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));

	glEnable(GL_DEPTH_TEST);

	//we capture the cursor
	glfwSetInputMode(glfwGetCurrentContext(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(glfwGetCurrentContext(), VexGL::Core::Gameclass::mouse_callback);

	glfwGetWindowSize(glfwGetCurrentContext(), &WindowHeight, &WindowWidth);
}

void VexGL::Core::Gameclass::Render() {

	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

	glClearColor(0.1f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(shaderProgram);

	//glBindTexture(GL_TEXTURE_2D, texture);

	//glUniform1i(glGetUniformLocation(shaderProgram, "Texture"), texture);

	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	glUniform1f(glGetUniformLocation(shaderProgram, "Xoffset"), Xoffset);
	glUniform1f(glGetUniformLocation(shaderProgram, "Yoffset"), Yoffset);
	glUniform1f(glGetUniformLocation(shaderProgram, "Opacity"), Opacity);

	//we send the transform value to the vertex shader like this
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "transform"), 1, false, glm::value_ptr(trans));

	int width; int height;
	glfwGetWindowSize(glfwGetCurrentContext(), &width, &height);
	glViewport(0, 0, width, height);
	glfwSwapBuffers(glfwGetCurrentContext());
}

#pragma warning (push)
#pragma warning (disable: 4244)
#pragma warning (disable: 4305)

void VexGL::Core::Gameclass::Update() {
	DeltaTime = glfwGetTime() - LastFrame;
	LastFrame = glfwGetTime();
	FrameSinceStart++;

	//camYaw = -90.0f;

	cameraDirection.x = glm::cos(glm::radians(camYaw)) * glm::cos(glm::radians(camPitch));
	cameraDirection.y = glm::sin(glm::radians(camPitch));
	cameraDirection.z = glm::sin(glm::radians(camYaw)) * glm::cos(glm::radians(camPitch));
	
	//cameraPosition = glm::vec3(camX, camY, camZ);

	cameraFront = glm::normalize(cameraDirection);

	view = glm::mat4(1.0f);
	//on crééer une martrice look at.
	view = glm::lookAt(cameraPosition, cameraPosition + cameraFront, up);

	trans = glm::mat4(1.0f);
	model = glm::mat4(1.0f);
	//model = glm::rotate(model,glm::radians(270+40.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(Rotation), glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::scale(model, glm::vec3(Scale * Direction, Scale, Scale));
	model = glm::translate(model, glm::vec3(Xoffset * Direction, Yoffset, 0.0f));

	if (FrameSinceStart % 10 == 0) {
		std::cout << 1 / DeltaTime << " FPS" << std::endl;
	}

	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_W) == GLFW_PRESS) {
		cameraPosition += 1 * (float)DeltaTime * cameraFront;
	}

	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_S) == GLFW_PRESS) {
		cameraPosition -= 1 * (float)DeltaTime * cameraFront;
	}

	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_D) == GLFW_PRESS) {
		cameraPosition += 1 * (float)DeltaTime * glm::normalize(glm::cross(cameraFront,cameraUp));
	}

	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_A) == GLFW_PRESS) {
		cameraPosition -= 1 * (float)DeltaTime * glm::normalize(glm::cross(cameraFront, cameraUp));
	}

	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_R) == GLFW_PRESS)
	{
		cameraPosition += 1 * (float)DeltaTime * cameraUp;
	}

	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_F) == GLFW_PRESS)
	{
		cameraPosition -= 1 * (float)DeltaTime * cameraUp;
	}

	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_Q) == GLFW_PRESS)
	{
		Rotation -= 50 * DeltaTime;
	}

	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_E) == GLFW_PRESS)
	{
		Rotation += 50 * DeltaTime;
	}

	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_UP) == GLFW_PRESS)
	{
		Scale += 1 * DeltaTime;
	}

	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		Scale -= 1 * DeltaTime;
	}
}

#pragma warning (pop)

void VexGL::Core::Gameclass::KeyCallBack(GLFWwindow* window, int key, int scancode, int action, int mods) {
	
	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
		switch (iswireframe) {
			case true:
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
				break;
			case false:
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
				break;
		};
		iswireframe = !iswireframe;
	}
	if (key == GLFW_KEY_KP_ADD && action == GLFW_PRESS ) {
		Opacity += 0.2f;
		if(Opacity >= 1) Opacity = 1;
	}
	if (key == GLFW_KEY_KP_SUBTRACT && action == GLFW_PRESS ) {
		Opacity -= 0.2f;
		if (Opacity <= 0) Opacity = 0;
	}
}

float lastMouseX = 0;
float lastMouseY = 0;

float VexGL::Core::Gameclass::camYaw;
float VexGL::Core::Gameclass::camPitch;

void VexGL::Core::Gameclass::mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	float xoffset = xpos - lastMouseX;
	float yoffset = lastMouseY - ypos; // reversed since y-coordinates range from bottom to top
	lastMouseX = xpos;
	lastMouseY = ypos;

	const float sensitivity = 0.1f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	VexGL::Core::Gameclass::camYaw += xoffset;
	VexGL::Core::Gameclass::camPitch += yoffset;

	if (VexGL::Core::Gameclass::camPitch > 89.0f)
		VexGL::Core::Gameclass::camPitch = 89.0f;
	if (VexGL::Core::Gameclass::camPitch < -89.0f)
		VexGL::Core::Gameclass::camPitch = -89.0f;

}
