#pragma once
#include  <iostream>
#include <glad/glad.h>
#include <glfw3.h>
#include <stb_image.h>

namespace VexGL
{
	class TextureLoader
	{
		public:
			static unsigned int CreateTexture2DFromFile(std::string Filepath, int* Width, int* Height, int* ColorChannelNbr, int format,bool ImageFLip, int GL_TEXTURE_N);
	};

}

