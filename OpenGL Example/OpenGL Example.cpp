// OpenGL Example.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <stdio.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

// Window dimensions
const GLint WIDTH = 800, HEIGHT = 600;

GLuint VAO, VBO, shader;

// Vertex Shader
static const char* vShader = "                                  \n\
#version 330                                                    \n\
                                                                \n\
layout (location = 0) in vec3 pos;                              \n\
                                                                \n\
void main()                                                     \n\
{                                                               \n\
    gl_Position = vec4(0.4 * pos.x, 0.4 * pos.y, pos.z, 1.0);   \n\
                                                    \n\
}                                                               \n\
";

// Fragment Shader
static const char* fShader = "                                  \n\
#version 330                                                    \n\
                                                                \n\
out vec4 color;                                                 \n\
                                                                \n\
void main()                                                     \n\
{                                                               \n\
    color = vec4(1.0, 0.0, 0.0, 1.0);                           \n\
                                                                \n\
}                                                               \n\
";


void CreateTriangle()
{
    GLfloat vertices[] = {
        -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        0.0f, 1.0f, 0.0f
    };

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
}

void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType)
{
    return;
}

void CompileShaders() {
    //from GLint
    shader = glCreateProgram();

    if (!shader)
    {
        printf("Error creating shader !!\n");
        return;
    }

    AddShader(shader, vShader, GL_VERTEX_SHADER);
    AddShader(shader, fShader, GL_FRAGMENT_SHADER);

    GLint result = 0;
    GLchar eLog[1024] = { 0 };

    glLinkProgram(shader);
    glGetProgramiv(shader, GL_LINK_STATUS, &result);
    if (!result)
    {
        glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
        printf("Error Linking Program !: %s \n", eLog);
        return;
    }

    glValidateProgram(shader);
	glGetProgramiv(shader, GL_LINK_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
		printf("Error Validate Program !: %s \n", eLog);
		return;
	}

}

int main()
{
    // init GLFW
    if (!glfwInit())
    {
        std::cout << "GLFW init failed" << std::endl;
        glfwTerminate();
        return 1;
    }

    // Setup GLFW Window properties
    // OpenGL version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);    
    // Core profile = no backwards compatibility
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // allow forward compatibility
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow* mainWindow = glfwCreateWindow(WIDTH, HEIGHT, "Test Window", NULL, NULL);
    if (!mainWindow) {
        std::cout << "GLFW Window Creation failed!" << std::endl;

    }

    // Get Buffer size information
    int bufferWidth, bufferHeight;
    glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

    // Set Context for GLEW to USE
    glfwMakeContextCurrent(mainWindow);

    // Allow Modern Extension features
    glewExperimental = GL_TRUE;

    if (glewInit() != GLEW_OK)
    {
        printf("GLEW Init Failed!");
        glfwDestroyWindow(mainWindow);
        glfwTerminate();
        return 1;
    }

    // Setup Viewport Size
    glViewport(0, 0, bufferWidth, bufferHeight);

    // Loop until window closed
    while (!glfwWindowShouldClose(mainWindow))
    {
        // Get + Handle user input events
        glfwPollEvents();

        // clear window
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(mainWindow);
    }

    return 0;
    
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
