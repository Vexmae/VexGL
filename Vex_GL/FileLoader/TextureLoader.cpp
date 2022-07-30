#include "TextureLoader.h"

//Créé une texture et renvoie sont ID sous forme d'un unsigned integer
//
//Arguments:
//	1: Chemin relatif à l'executable
//	2: Variable à laquelle assigner la largeur de l'image
//	3: Variable à laquelle assigner la longeur de l'image
//	4: Variable à laquelle assigner le nombre de canal de couleur de l'image
//	5: Le format de la texture (Par exemple GL_RGBA, GL_RGB)
//	6: Si l'image doit être retournée
//	7: Texture Unit auquel assigner la texture (Par exemple GL_TEXTURE0, GL_TEXTURE7 ...)
unsigned int VexGL::TextureLoader::CreateTexture2DFromFile(std::string Filepath, int* Width, int* Height, int* ColorChannelNbr, int TextureColorFormat, bool ImageFLip, int GL_TEXTURE_N)
{
	stbi_set_flip_vertically_on_load(ImageFLip);
	unsigned char*  imagedata = stbi_load(Filepath.c_str(), Width, Height, ColorChannelNbr, 0);
	if (imagedata) { std::cout << "Texture '" << Filepath << "' Loaded  without error" << std::endl; }
	else { std::cout << "Error while loading texture '" << Filepath << "'" << std::endl; }

	unsigned int TextureID;
	glGenTextures(1, &TextureID);
	glActiveTexture(GL_TEXTURE_N);
	glBindTexture(GL_TEXTURE_2D, TextureID);

	//Utilisé pour générer la texture à partir des données, la texture générée est attaché à la texture qu'on a lié juste au dessus
	glTexImage2D(GL_TEXTURE_2D, 0, TextureColorFormat, *Width, *Height, 0, TextureColorFormat, GL_UNSIGNED_BYTE, imagedata);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(imagedata);

	return TextureID;
}
