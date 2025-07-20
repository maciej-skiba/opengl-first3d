#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "functions.hpp"
#include "vertices.hpp" 

extern float boxVertices[];

int main(void)
{
    GLFWwindow* window;
    int initSuccess = 1;

    if (InitializeOpenGL(window) != initSuccess)
    {
        return -1;
    }

    unsigned int VAO;
    
    const char* vertexShaderPath = "../shaders/3.3.vert.shad";
    const char* fragmentShaderPath = "../shaders/3.3.frag.shad";

    const char* whiteColorShaderPath = "../shaders/3.3.whitefrag.shad";

    Shader shader(vertexShaderPath, fragmentShaderPath);
    Shader outlineShader(vertexShaderPath, whiteColorShaderPath);

    int numOfVerticesInBox = 36;
    int numOfBoxes = 4;

    glm::vec3 boxPositions[] = {
        glm::vec3( 0.0f,  -3.0f, -10.0f), 
        glm::vec3( 1.5f,  0.0f, -15.0f), 
        glm::vec3( -4.0f, -0.2f, -12.5f),  
        glm::vec3(-1.0f, -1.0f, -12.3f),  
    };

    CreateBoxVao(VAO, boxVertices, numOfVerticesInBox);

    glEnable(GL_DEPTH_TEST);

    while (!glfwWindowShouldClose(window))
    {
        float timeValue = glfwGetTime();
        float blueValue = sin(timeValue) / 2.0f + 0.5f;

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glBindVertexArray(VAO);

        for (int boxIndex = 0; boxIndex < numOfBoxes; boxIndex++)
        {
            int vertexBlueColorLocation = glGetUniformLocation(shader.ID, "blueColor");
            glUniform1f(vertexBlueColorLocation, blueValue);

            glm::mat4 model = glm::mat4(1.0f);
            model = glm::rotate(model, timeValue, glm::normalize(glm::vec3(1.0f + boxIndex, 0.0f, 4.0f - boxIndex)));
            
            glm::mat4 view = glm::mat4(1.0f);
            view = glm::translate(view, boxPositions[boxIndex]); 

            glm::mat4 projection = glm::mat4(1.0f);
            projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

            // --- wypełnienie trójkątów ---

            shader.UseProgram();

            unsigned int modelLocation = glGetUniformLocation(shader.ID, "model");
            glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));
            unsigned int viewLocation = glGetUniformLocation(shader.ID, "view");
            glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(view));
            unsigned int projectionLocation = glGetUniformLocation(shader.ID, "projection");
            glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projection));
            
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            glEnable(GL_POLYGON_OFFSET_FILL);
            glPolygonOffset(1.0, 1.0); // żeby linie nie zlewały się z powierzchnią
            glDrawArrays(GL_TRIANGLES, 0, numOfVerticesInBox);

            // -------------------------

            // --- outline trójkątów ---

            outlineShader.UseProgram();

            modelLocation = glGetUniformLocation(outlineShader.ID, "model");
            glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));
            viewLocation = glGetUniformLocation(outlineShader.ID, "view");
            glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(view));
            projectionLocation = glGetUniformLocation(outlineShader.ID, "projection");
            glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projection));

            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            glDisable(GL_POLYGON_OFFSET_FILL);
            glLineWidth(2.0f); // grubość krawędzi
            glDrawArrays(GL_TRIANGLES, 0, numOfVerticesInBox);

            // -------------------------
        }
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}