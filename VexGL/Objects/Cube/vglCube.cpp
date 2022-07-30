#include "vglCube.h"

void vglCube::vglInitCube() {
	_model = glm::mat4(1);
	_positionVector = glm::vec3(0.0f);
	_rotationVector = glm::vec3(0.0f);
	_scaleVector = glm::vec3(1.0f);

	glGenVertexArrays(1, &_VAO);
	glBindVertexArray(_VAO);

	glGenBuffers(1, &_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, _VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(_vertices), _vertices, GL_STATIC_DRAW);

	glGenBuffers(1, &_EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(_indices), _indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, false, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
}

void vglCube::vglTranslate(glm::vec3 translationVector) {
	_positionVector += translationVector;
}

void vglCube::vglSetPosition(glm::vec3 positionVector) {
	_positionVector = positionVector;
}

void vglCube::vglSetPosition(float x, float y, float z) {
	_positionVector = glm::vec3(x, y, z);
}

void vglCube::vglRotate(glm::vec3 rotationVector) {
	_rotationVector += rotationVector;
}

void vglCube::vglScale(glm::vec3 scaleVector) {
	_scaleVector = scaleVector;
}

void vglCube::vglAddScale(glm::vec3 scaleVector) {
	_scaleVector += scaleVector;
}

void vglCube::vglGetPosition(float* x, float* y, float* z) {
	*x = _positionVector.x;
}

void vglCube::vglGetBuffers(unsigned int* VAO, unsigned int* VBO, unsigned int* EBO) {
	*VAO = _VAO;
	*VBO = _VBO;
	*EBO = _EBO;
}

void vglCube::vglGetVertices(float* vertices[]) {
	*vertices = _vertices;
}

void vglCube::vglGetIndices(unsigned int* indices[]) {
	*indices = _indices;
}

void vglCube::vglDraw(unsigned int shaderProgram) {
	glBindVertexArray(_VAO);

	_model = glm::mat4(1);

	_model = glm::scale(_model, _scaleVector);

	_model = glm::translate(_model, _positionVector);

	_model = glm::rotate(_model, glm::radians(_rotationVector.z), glm::vec3(0.0f, 0.0f, 1.0f));
	_model = glm::rotate(_model, glm::radians(_rotationVector.y), glm::vec3(0.0f, 1.0f, 0.0f));
	_model = glm::rotate(_model, glm::radians(_rotationVector.x), glm::vec3(1.0f, 0.0f, 0.0f));

	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"),1,false,glm::value_ptr(_model));

	glDrawElements(GL_TRIANGLES, sizeof(_vertices) / sizeof(_vertices[0]), GL_UNSIGNED_INT, (void*)0);

	glBindVertexArray(0);
}
