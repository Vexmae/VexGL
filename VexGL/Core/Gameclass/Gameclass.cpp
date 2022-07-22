#include "Gameclass.h"

float VexGL::Core::Gameclass::Xoffset;
float VexGL::Core::Gameclass::Yoffset;
float VexGL::Core::Gameclass::Opacity;
int VexGL::Core::Gameclass::Direction;
bool VexGL::Core::Gameclass::iswireframe;

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
	glVertexAttribPointer(0,3,GL_FLOAT,false,8*sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//Color Attributes
	//Le premier chiffre correspond au layout location du shader vertex, le nombre de valeur de notre info (ici 3 pour RGB), le type des valeurs, false, 
	//la taille en mémoire de chaque vertex, le offset en mémoire du début des valeurs (ici 3 fois la taille d'un float (qui correspond à passer les 3 première valeurs de position))
	glVertexAttribPointer(1, 3, GL_FLOAT, false, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1); //On active l'attrib pointer 1

	glVertexAttribPointer(2, 2, GL_FLOAT, false, 8 * sizeof(float), (void*)(6 * sizeof(float)));
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


	glGenTextures(1, &texture0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture0);

	//On utilise ceci car les images ont souvent le 0.0 en haut alors que nous le voulons en bas
	stbi_set_flip_vertically_on_load(true);

	//On lie la texture et stocke ses données sous la forme d'un array de byte.
	int width, height, nbrcolor;
	unsigned char* image0data = stbi_load("../x64/Debug/container.jpg", &width, &height, &nbrcolor, 0);

	if (image0data == NULL) {
		std::cout << "Imagedata nul" << stbi_failure_reason() << std::endl;
	}
	
	//Utilisé pour générer la texture à partir des données, la textuire générée est attaché à la texture qu'on a lié juste au dessus
	
	//La cible à générer, ici on veut une texture 2D
	//Le niveau de mipmap qu'on souhait, ici on vas le laisser à 0
	//Le format dans lequel on souhaite qu'openGL garde la texture, ici en format RGB
	//La largeur de l'image
	//La hauteur de l'image
	//Cet argument doit otujours être 0
	//Le format de l'image de base
	//Le type de donnée de l'image de base, ici un unsigned char (byte)
	//les données de l'image
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image0data);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(image0data); //On libère imagedata de la mémoire.
	

	glGenTextures(1, &texture1);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture1);

	unsigned char* image1data = stbi_load("../x64/Debug/megaman.png", &width, &height, &nbrcolor, 0);

	if (image1data == NULL) {
		std::cout << "Imagedata nul" << stbi_failure_reason() << std::endl;
	}

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image1data);
	glGenerateMipmap(GL_TEXTURE_2D);

	//Now we tell openGL which texture is which
	//On dit que l'uniform "Texture0" est égal à GL_TEXTURE0 ((on écrit juste 0))
	glUniform1i(glGetUniformLocation(shaderProgram, "Texture0"), 0);
	glUniform1i(glGetUniformLocation(shaderProgram, "Texture1"), 1);

	Direction = 1;
	Opacity = 0.5;
	iswireframe = false;
	glfwSetKeyCallback(glfwGetCurrentContext(), KeyCallBack );
}

void VexGL::Core::Gameclass::Render() {

	glClearColor(0.1f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(shaderProgram);

	//glBindTexture(GL_TEXTURE_2D, texture);

	//glUniform1i(glGetUniformLocation(shaderProgram, "Texture"), texture);

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	glUniform1f(glGetUniformLocation(shaderProgram, "Xoffset"), Xoffset);
	glUniform1f(glGetUniformLocation(shaderProgram, "Yoffset"), Yoffset);
	glUniform1f(glGetUniformLocation(shaderProgram, "Opacity"), Opacity);
	glUniform1i(glGetUniformLocation(shaderProgram, "Direction"), Direction);

	int width; int height;
	glfwGetWindowSize(glfwGetCurrentContext(), &width, &height);
	glViewport(0, 0, width, height);
	glfwSwapBuffers(glfwGetCurrentContext());
}



void VexGL::Core::Gameclass::Update() {
	DeltaTime = glfwGetTime() - LastFrame;
	LastFrame = glfwGetTime();
	FrameSinceStart++;

	if (FrameSinceStart % 10 == 0) {
		std::cout << 1 / DeltaTime << " FPS" << std::endl;
	}
	

	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_UP) == GLFW_PRESS) {
		Yoffset += 1 * DeltaTime;
	}

	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_DOWN) == GLFW_PRESS) {
		Yoffset -= 1 * DeltaTime;
	}

	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_RIGHT) == GLFW_PRESS) {
		Xoffset += 1 * DeltaTime;
		Direction = 1;
	}

	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_LEFT) == GLFW_PRESS) {
		Xoffset -= 1 * DeltaTime;
		Direction = -1;
	}
}

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
		Opacity += 0.2;
		if(Opacity >= 1) Opacity = 1;
	}
	if (key == GLFW_KEY_KP_SUBTRACT && action == GLFW_PRESS ) {
		Opacity -= 0.2;
		if (Opacity <= 0) Opacity = 0;
	}
}
