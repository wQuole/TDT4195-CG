// Local headers
#include "program.hpp"
#include "gloom/gloom.hpp"
#include "gloom/shader.hpp"
#include "vector"

GLuint setUpVAOTriangle(std::vector<GLfloat> vertexCoords, std::vector<GLuint> vertexIndices);

GLuint setUpVAOTriangle(std::vector<GLfloat> *vertexCoords, std::vector<GLuint> *vertexIndices)
{
    size_t vectorSizeInBytes = vertexCoords->size() * sizeof(GLfloat);                                              
    auto dataWhichShouldBeCopiedToTheGPU = vertexIndices->size() * sizeof(GLuint);

    // Bind the Vertex Array Object (VAO)
    GLuint vertexArrayID = 0;
    glGenVertexArrays(1, &vertexArrayID);
    glBindVertexArray(vertexArrayID);

    // Create Vertex Buffer Object (VBO)
    GLuint vertexBufferID = 0;
    glGenBuffers(1, &vertexBufferID);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
    glBufferData(GL_ARRAY_BUFFER, vectorSizeInBytes, &vertexCoords->front(), GL_STATIC_DRAW);

    // Set Vertex Attribute Pointer (VAP)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, GL_ZERO, GL_ZERO);
    glEnableVertexAttribArray(0);

    // Set index buffer
    GLuint indexBufferID = 0;
    glGenBuffers(1, &indexBufferID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, dataWhichShouldBeCopiedToTheGPU, &vertexIndices->front(), GL_STATIC_DRAW);

    return vertexBufferID;
}


void runProgram(GLFWwindow* window)
{
    // Enable depth (Z) buffer (accept "closest" fragment)
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    // Configure miscellaneous OpenGL settings
    glEnable(GL_CULL_FACE);

    // Set default colour after clearing the colour buffer
    glClearColor(0.3f, 0.5f, 0.8f, 1.0f);

    // Set up your scene here (create Vertex Array Objects, etc.)
    Gloom::Shader shader;
    shader.makeBasicShader("../gloom/shaders/simple.vert",
                           "../gloom/shaders/simple.frag");

    std::vector<GLfloat> triangleCoordinates {
        -0.6, -0.6, 0.0,
        0.6, -0.6, 0.0,
        0.0, 0.6, 0.0
    };

    std::vector<GLuint> triangleIndices;

    triangleIndices.reserve(triangleCoordinates.size());
    // Fill the indices
    for (uint i = 0; i < triangleCoordinates.size() ; ++i) triangleIndices.push_back(i);

    //GLuint triAngleVAO = setUpVAOTriangle(triangleCoordinates, triangleIndices);

    // Rendering Loop
    while (!glfwWindowShouldClose(window))
    {
        // Clear colour and depth buffers
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Draw your scene here
        //shader.activate();
        //glBindVertexArray(triAngleVAO);

        //glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, GL_ZERO);

        //shader.deactivate();
        //printGLError();
        
        // Handle other events
        glfwPollEvents();
        handleKeyboardInput(window);

        // Flip buffers
        glfwSwapBuffers(window);
    }
}

void handleKeyboardInput(GLFWwindow* window)
{
    // Use escape key for terminating the GLFW window
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}
