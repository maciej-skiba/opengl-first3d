#include "functions.hpp" 
#include "stb_image.h"
#include "texture.hpp"

void FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void SetupTexture(const char* path, int &width, int &height, int &nrChannels, int colorType, bool linearFiltering)
{
    // set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    if (linearFiltering)
    {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }
    else
    {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    }

    // load and generate the texture
    unsigned char *data = stbi_load(path, &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, colorType, width, height, 0, colorType, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }

    stbi_image_free(data);
}

void Texture::ReloadTexture(bool linFiltering)
{
    linearFiltering = linFiltering;
    SetupTexture(_path, _width, _height, _nrChannels, _colorType, linearFiltering);
}

void ProcessInput
    (GLFWwindow *window, Shader* shader, glm::vec3 &spinnerPosition,
    float spinnerWidth, float &rotationDirection, std::map<int, bool> &keyPressedTrackingMap)
{
    float movementSpeed = 0.02f;

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS && spinnerPosition.y < 1.0f - spinnerWidth)
    {
        spinnerPosition.y += movementSpeed;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS && spinnerPosition.y > -1.0f + spinnerWidth)
    {
        spinnerPosition.y -= movementSpeed;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS && spinnerPosition.x < 1.0f - spinnerWidth)
    {
        spinnerPosition.x += movementSpeed;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS && spinnerPosition.x > -1.0f + spinnerWidth)
    {
        spinnerPosition.x -= movementSpeed;
    }

    // change rotation direction to opposite with GetKeyDown
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
    {
        if (keyPressedTrackingMap[GLFW_KEY_SPACE] == false)
        {
            rotationDirection *= -1.0f;
            keyPressedTrackingMap[GLFW_KEY_SPACE] = true;
        }
    }
    else (keyPressedTrackingMap[GLFW_KEY_SPACE] = false);

    //std::cout << "x: " << spinnerPosition.x << " y: " << spinnerPosition.y << std::endl;
}