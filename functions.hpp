#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>
#include "shader.hpp"
#include <map>

void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
void SetupTexture(const char* path, int &width, int &height, int &nrChannels, int colorType, bool linearFiltering);
void ProcessInput
    (GLFWwindow *window, Shader* shader, glm::vec3 &spinnerPosition,
    float spinnerWidth, float &rotationDirection, std::map<int, bool> &keyPressedTrackingMap);