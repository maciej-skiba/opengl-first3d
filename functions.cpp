#include "functions.hpp"

int numOfDimensionsInVertex = 3;
int amountOfVerticesInTriangle = 3;
int amountOfCircleCenterVertices = 1;

int InitializeOpenGL(GLFWwindow*& window)
{
        /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK)
    {
        std::cout << "cant load glew" << std::endl;
    }

    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    return 1;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
    if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
    {
        glClearColor(0.45f, 0.91f, 0.45f, 1);
    }
}

void CreateBoxVao(
    unsigned int &VAO, 
    float* boxVertices,
    int numOfVertices)
{   
    //Vertex Array Object
    glGenVertexArrays(1, &VAO); // tworzy VAO
    glBindVertexArray(VAO);   //aktywacja tego VAO
    
    //Vertex Buffer Object
    unsigned int VBO;
    glGenBuffers(1, &VBO); //tworzy pusty VBO

    glBindBuffer(GL_ARRAY_BUFFER, VBO); //ustaw VBO jako aktywny array buffer; wszelkie rzeczy na GL_ARRAY_BUFFER będą dotyczyły obiektu VBO
    glBufferData(GL_ARRAY_BUFFER, numOfVertices * numOfDimensionsInVertex * sizeof(float), boxVertices, GL_STATIC_DRAW); //wypełnij bufor (GPU) danymi

    glVertexAttribPointer(
        0,                  // index = location w shaderze (0 dla aPos)
        3,                  // ile wartości (vec3 → 3)
        GL_FLOAT,           // typ danych
        GL_FALSE,           // normalizacja
        3 * sizeof(float),  // odstęp między kolejnymi atrybutami (stride)
        (void*)0            // offset od początku
    );
    glEnableVertexAttribArray(0); //wybierz layout 0 jako aktywny
}