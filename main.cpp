#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "functions.hpp" 

int main(void)
{
    GLFWwindow* window;
    int initSuccess = 1;

    if (InitializeOpenGL(window) != initSuccess)
    {
        return -1;
    }

    unsigned int VAO;
    
    int amountOfTrianglesInCircle = 100;
    extern int numOfDimensionsInVertex;
    extern int amountOfCircleCenterVertices;

    const char* vertexShaderPath = "../shaders/3.3.vert.shad";
    const char* fragmentShaderPath = "../shaders/3.3.frag.shad";

    Shader shader(vertexShaderPath, fragmentShaderPath);

    CreateCircle(VAO, amountOfTrianglesInCircle);

    // -- uncomment to see the outline only --
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    while (!glfwWindowShouldClose(window))
    {
        //processInput(window);
        /* Render here */
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader.UseProgram();

        float timeValue = glfwGetTime();
        float blueValue = sin(timeValue) / 2.0f + 0.5f;
        int vertexBlueColorLocation = glGetUniformLocation(shader.ID, "blueColor");
        glUniform1f(vertexBlueColorLocation, blueValue);

        // rotate using transformation matrix 
        unsigned int transformLoc = glGetUniformLocation(shader.ID, "transform");
        glm::mat4 transMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        transMatrix = glm::translate(transMatrix, glm::vec3(sin(timeValue) / 5.0f , cos(timeValue) / 5.0f, 0.0f));
        transMatrix = glm::rotate(transMatrix, timeValue, glm::vec3(0.0f, 0.0f, 1.0f));
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transMatrix));

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, (amountOfTrianglesInCircle + amountOfCircleCenterVertices) * numOfDimensionsInVertex, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}