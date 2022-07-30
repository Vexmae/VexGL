#pragma once
#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../../Graphics/Shader/vglShader.h"

#include <iostream>

/// @brief A cube object that can be rendered on screen, to use it, declare the object then call vglInitCube() to initialize it.
class vglCube {

	public:	
		/// @brief This function initialize the object and create all its shader, BO, EBO and VAO. It can't be a constructor because the constructor is executed before GLAD and GLFW is initialized.
		void vglInitCube();

		/// @brief Translates the model in the world using the desired vector
		/// @param translationVector: Vector used to translate the model in the world
		void vglTranslate(glm::vec3 translationVector);

		/// @brief Set position of the object to the provided vector from 0,0,0
		/// @param positionVector: Vector  to the position desired from 0,0,0
		void vglSetPosition(glm::vec3 positionVector);
		/// @brief Set position of the obejct to the provided world coordinates
		/// @param x: x axis position
		/// @param y: y axis position
		/// @param z: z axis position
		void vglSetPosition(float x, float y, float z);

		/// @brief Rotates the model using the provided vector around the center of the model
		/// @param rotationVector: Vector containing the rotation desired in degrees, to roate 70 degres on x-axis, use vec3(70.0f,0.0f,0.0f)
		void vglRotate(glm::vec3 rotationVector);

		/// @brief Set the rotation of the object to the provided vector
		/// @param rotationVector: Vector containing the rotation desired in degrees, to roate 70 degres on x-axis, use vec3(70.0f,0.0f,0.0f)
		void vglSetRotation(glm::vec3 rotationVector);

		/// @brief Changes the scale of the model using the provided vector
		/// @param scaleVector: The vector used to scale the cube
		void vglScale(glm::vec3 scaleVector);

		/// @brief *ADD* the provided vector  to  the scale vector
		/// @param scaleVector: The vector used to scale the cube
		void vglAddScale(glm::vec3 scaleVector);


		void vglGetPosition(float* x, float* y, float* z);
		void vglGetBuffers(unsigned int* VAO, unsigned int* VBO, unsigned int* EBO);
		void vglGetVertices(float* vertices[]);
		void vglGetIndices(unsigned int* indices[]);

		void vglDraw(unsigned int shaderProgram);
	private:
		unsigned int _VAO, _VBO, _EBO;

		float _vertices[128] = {
		0.5f,0.5f,0.5f, //top right
		0.5f,-0.5f,0.5f, //bottom right
		-0.5f,-0.5f,0.5f, //bottom left
		-0.5,0.5f,0.5f, //top left
		//layer2
		0.5f,0.5f,-0.5f, //top right
		0.5f,-0.5f,-0.5f, //bottom right
		-0.5f,-0.5f,-0.5f, //bottom left
		-0.5,0.5f,-0.5f, //top left
		};

		unsigned int _indices[128] = {
			0,1,2,
			0,2,3,
			0,1,5,
			0,4,5,
			0,3,7,
			0,4,7,
			1,2,6,
			1,5,6,
			2,3,6,
			3,6,7,
			4,6,7,
			4,5,6
		};

		glm::mat4 _model;

		glm::vec3 _rotationVector, _scaleVector, _positionVector;
};

