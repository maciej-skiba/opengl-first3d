#pragma once

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <math.h>
#include <fstream>
#include <sstream>
#include "shader.hpp"

int InitializeOpenGL(GLFWwindow*& window);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
void CreateBoxVao(unsigned int &VAO, float* boxVertices, int numOfVertices);
std::string LoadShader(const std::string& shaderPath);
void CheckShaderCompilation(unsigned int vertexShader);
void CheckShaderLink(unsigned int shaderProgram);
void PrintArray(float* arr, int size);