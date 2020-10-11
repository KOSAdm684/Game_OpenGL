#include <stdio.h>
#include <iostream>
#include "Shader/Shader.h"
#include <GLFW/glfw3.h>

int main()
{
    glfwInit();
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_ANY_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    int width = 1024;
    int height = 768;
    const float *proj = new float[2]{ (float)2/width, (float)2/height };
    bool *states = new bool[4] { 0, 0, 0, 0 };
    const float acceleration = 0.05f;
    float *speeds = new float[4] { 1.0f, 1.0f, 1.0f, 1.0f };
    // Create a GLFWwindow
    GLFWwindow *window = glfwCreateWindow(width, height, "title", nullptr, nullptr);
    if (!window) {
        std::cout << "Could not initialize window.";
        std::cin.get();
        exit(1);
    }
    glfwMakeContextCurrent(window);

    // Set Viewport to fill window
    glViewport(0, 0, width, height);
    
    glewExperimental = GL_TRUE;
    glewInit();
    
    Shader *shdr = new Shader("Shaders/tr.vert", "Shaders/tr.frag");

    GLfloat vertices[] = {
        -50.0f, -30.0f, 0.0f, 0.0f, 0.0f,
        -30.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        -10.0f, -30.0f, 0.0f, 0.0f, 0.0f
    };

    GLuint VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(2 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);

    while (!glfwWindowShouldClose(window))
    {   
        glfwPollEvents();
        states[0] = glfwGetKey(window, GLFW_KEY_A);
        states[1] = glfwGetKey(window, GLFW_KEY_D);
        states[2] = glfwGetKey(window, GLFW_KEY_W);
        states[3] = glfwGetKey(window, GLFW_KEY_S);

        if (states[0])
        {
            vertices[0] -= speeds[0];
            vertices[5] -= speeds[0];
            vertices[10] -= speeds[0];
            speeds[0] += acceleration;
        }
        else
        {
            speeds[0] = 1.0f;
        }
        if (states[1])
        {
            vertices[0] += speeds[1];
            vertices[5] += speeds[1];
            vertices[10] += speeds[1];
            speeds[1] += acceleration;
        }
        else
        {
            speeds[1] = 1.0f;
        }
        if (states[2])
        {
            vertices[1] += speeds[2];
            vertices[6] += speeds[2];
            vertices[11] += speeds[2];
            speeds[2] += acceleration;
        }
        else
        {
            speeds[2] = 1.0f;
        }
        if (states[3])
        {
            vertices[1] -= speeds[3];
            vertices[6] -= speeds[3];
            vertices[11] -= speeds[3];
            speeds[3] += acceleration;
        }
        else
        {
            speeds[3] = 1.0f;
        }

        glClearColor(1, 1, 1, 0);
        glClear(GL_COLOR_BUFFER_BIT);

        shdr->Use();
        GLuint u_proj = glGetUniformLocation(shdr->Program, "u_projection");
        glUniform2fv(u_proj, 1, proj);
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);

        glfwSwapBuffers(window);
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glfwTerminate();
    
    return 0;
}