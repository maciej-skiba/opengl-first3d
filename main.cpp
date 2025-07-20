#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <list>
#include <memory>

#include "texture.hpp"
#include "functions.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

float vertices[] = {
    // positions          // texture coords
     0.5f,  0.5f, 0.0f,   1.0f, 1.0f,   // top right
     0.5f, -0.5f, 0.0f,   1.0f, 0.0f,   // bottom right
    -0.5f, -0.5f, 0.0f,   0.0f, 0.0f,   // bottom left
    -0.5f,  0.5f, 0.0f,   0.0f, 1.0f    // top left 
};

unsigned int indices[] = {
    0, 1, 3,   // first triangle
    1, 2, 3    // second triangle
};  

int main(void)
{ 
    GLFWwindow* window;

    if (!glfwInit()) return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(640, 480, "Shaders", NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK) std::cout << "Can't load GLEW\n";
    glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);  

    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    Shader myShader("shaders/3.3.shader.vshad", "shaders/3.3.shader.fshad");

    int width, height, nrChannels;

    bool linearFiltering = false;
    
    GLuint textureobj;

    glGenTextures(1, &textureobj);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureobj);

    Texture texture("textures/spinner.png", linearFiltering, GL_RGBA, &textureobj);
    float spinnerWidth = 0.9f;

    myShader.UseProgram();
    myShader.SetUniformInt("myTexture", 0);
        
    glEnable(GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glm::vec3 spinnerPosition(0.0f, 0.0f, 0.0f);
    float rotationDirection = -1.0f;
    float rotationSpeed = 2.0f;
    std::map<int, bool> keyPressedTracker = {{GLFW_KEY_SPACE, false}};

    while (!glfwWindowShouldClose(window))
    {
        ProcessInput(window, &myShader, spinnerPosition, spinnerWidth / 2.0f, rotationDirection, keyPressedTracker);
        glm::mat4 trans = glm::mat4(1.0f);
        trans = glm::translate(trans, spinnerPosition);
        trans = glm::rotate(trans, (float)glfwGetTime() * rotationSpeed, glm::vec3(0.0f, 0.0f, rotationDirection));
        myShader.SetUniformMat4("transform", trans);

        glClearColor (0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
               
        myShader.UseProgram();

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}