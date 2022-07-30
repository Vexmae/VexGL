#include "vglTime.h"

void vglTimeUpdate() {
	float time = glfwGetTime();
	_deltaTime = time - _lastFrameTime;
	_lastFrameTime = time;
	_frameSinceStart++;
}

float vglDeltaTime() {
	return _deltaTime;
}

void vglDeltaTime(float* deltaTime) {
	*deltaTime = _deltaTime;
}

unsigned int vglGetFrameSinceStart() {
	return _frameSinceStart;
}

void vglGetFrameSinceStart(unsigned int* frameSinceStart) {
	*frameSinceStart = _frameSinceStart;
}
