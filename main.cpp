#include <stdio.h>
#include <iostream>
#include "Shader/Shader.h"
#include <GLFW/glfw3.h>
#include "Tank/Tank.h"

int main()
{
    glfwInit();
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_ANY_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    int width = 1024; // [-512; 512]
    int height = 768; // [-384; 384]
    const float *proj = new float[2]{ (float)2/width, (float)2/height };
    bool *states = new bool[8] { 0, 0, 0, 0, 0, 0, 0, 0 };
    const float acceleration = 0.1f;
    float *speeds = new float[8] { 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f };
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
        -0.5f, -0.5f,
        -0.5f, 0.5f,
        0.5f, -0.5f,

        0.5f, -0.5f,
        0.5f, 0.5f,
        -0.5f, 0.5f
    };

    GLuint uProj = glGetUniformLocation(shdr->Program, "u_projection");
    GLuint uColor = glGetUniformLocation(shdr->Program, "u_color");
    GLuint uSize = glGetUniformLocation(shdr->Program, "u_size");
    GLuint uPosition = glGetUniformLocation(shdr->Program, "u_position");

    GLuint VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);

    Tank **tanks = new Tank*[2];
    tanks[0] = new Tank(-256, 0, 100, new float[3]{ 0.8f, 0.0f, 0.0f });
    tanks[1] = new Tank(256, 0, 100, new float[3] { 0.0f, 0.8f, 0.0f });


    while (!glfwWindowShouldClose(window))
    {   
        glfwPollEvents();
        states[0] = glfwGetKey(window, GLFW_KEY_A);
        states[1] = glfwGetKey(window, GLFW_KEY_D);
        states[2] = glfwGetKey(window, GLFW_KEY_W);
        states[3] = glfwGetKey(window, GLFW_KEY_S);
        states[4] = glfwGetKey(window, GLFW_KEY_LEFT);
        states[5] = glfwGetKey(window, GLFW_KEY_RIGHT);
        states[6] = glfwGetKey(window, GLFW_KEY_UP);
        states[7] = glfwGetKey(window, GLFW_KEY_DOWN);
        
        if (states[0] && !states[1])
        {
            tanks[0]->speedX -= acceleration;            
        }

        if (!states[0] && states[1])
        {
            tanks[0]->speedX += acceleration;
        }
        
        if (states[0] && states[1])
        {
            tanks[0]->speedX = 0;
        }

        if (!states[0] && !states[1])
        {
            tanks[0]->speedX = 0;
        }

        if (states[2] && !states[3])
        {
            tanks[0]->speedY += acceleration;
        }

        if (!states[2] && states[3])
        {
            tanks[0]->speedY -= acceleration;
        }

        if (states[2] && states[3])
        {
            tanks[0]->speedY = 0;
        }

        if (!states[2] && !states[3])
        {
            tanks[0]->speedY = 0;
        }

        // second tank
        if (states[4] && !states[5])
        {
            tanks[1]->speedX -= acceleration;            
        }

        if (!states[4] && states[5])
        {
            tanks[1]->speedX += acceleration;
        }
        
        if (states[4] && states[5])
        {
            tanks[1]->speedX = 0;
        }

        if (!states[4] && !states[5])
        {
            tanks[1]->speedX = 0;
        }

        if (states[6] && !states[7])
        {
            tanks[1]->speedY += acceleration;
        }

        if (!states[6] && states[7])
        {
            tanks[1]->speedY -= acceleration;
        }

        if (states[6] && states[7])
        {
            tanks[1]->speedY = 0;
        }

        if (!states[6] && !states[7])
        {
            tanks[1]->speedY = 0;
        }

        tanks[0]->Move();
        tanks[1]->Move();

        glClearColor(1, 1, 1, 0);
        glClear(GL_COLOR_BUFFER_BIT);

        shdr->Use();
        glUniform2fv(uProj, 1, proj);

        for (int i = 0; i < 2; i++)
        {
            glUniform3fv(uColor, 1, tanks[i]->color);
            glUniform2f(uPosition, tanks[i]->x, tanks[i]->y);
            glUniform1f(uSize, tanks[i]->size);
            glBindVertexArray(VAO);
            glDrawArrays(GL_TRIANGLES, 0, 6);
        }
        glBindVertexArray(0);

        glfwSwapBuffers(window);
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glfwTerminate();
    
    return 0;
}