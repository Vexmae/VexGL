#pragma once
#include <glad/glad.h>
#include <glfw/glfw3.h>

static float _lastFrameTime;
static float _deltaTime;
static unsigned int _frameSinceStart;

/// @brief Updates the time values
void vglTimeUpdate();

/// @brief Returns the time between this frame and the previous one
float vglDeltaTime();
/// @brief Sets given pointer to the time between this frame and the previous one
void vglDeltaTime(float* deltaTime);

/// @brief Returns the number of frame rendered 
unsigned int vglGetFrameSinceStart();
/// @brief Sets given pointer to the number of frame rendered
void vglGetFrameSinceStart(unsigned int* frameSinceStart);

