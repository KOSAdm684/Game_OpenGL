#include <stdio.h>
#include <iostream>
#include "Shader/Shader.h"
#include <GLFW/glfw3.h>
#include "Tank/Tank.h"
#include "Model/Model.h"
#include "Collection/Collection.h"
#include <math.h>

// Описать функцию проверки столкновений (формула в интернете)
// и абстракцию (класс) у которого будут все нужные общие параметры

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
    bool *states = new bool[10] { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
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
    
    // TODO Доделать башню

    glewExperimental = GL_TRUE;
    glewInit();
    
    Shader *shdr = new Shader("Shaders/tr.vert", "Shaders/tr.frag");

    TankModel tm = Model::readTankModel("res/tank.mdl");
    GunShellModel gsm = Model::readGunShellModel("res/gunShell.mdl");
    GLuint uProj = glGetUniformLocation(shdr->Program, "u_projection");
    GLuint uColor = glGetUniformLocation(shdr->Program, "u_color");
    GLuint uSize = glGetUniformLocation(shdr->Program, "u_size");
    GLuint uPosition = glGetUniformLocation(shdr->Program, "u_position");
    GLuint uAngle = glGetUniformLocation(shdr->Program, "u_angle");

    GLuint TankVBO, TankVAO;
    GLuint ShellVBO, ShellVAO;

    glGenVertexArrays(1, &TankVAO);
    glGenBuffers(1, &TankVBO);
    glGenVertexArrays(1, &ShellVAO);
    glGenBuffers(1, &ShellVBO);

    // Bind draw options and buffer for Tank
    glBindVertexArray(TankVAO);

    glBindBuffer(GL_ARRAY_BUFFER, TankVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * (tm.cvBody + tm.cvTower) * tm.countParams, tm.vertices, GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(2 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(ShellVAO);

    glBindBuffer(GL_ARRAY_BUFFER, ShellVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * gsm.cv * gsm.countParams, gsm.vertices, GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(2 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    Tank **tanks = new Tank*[2];
    Collection* gsCollection = new Collection();
    tanks[0] = new Tank(-256, 0, 100, new float[3] { 0.8f, 0.0f, 0.0f }, M_PI_2, 0.05f, 0.2f, 3.0f, -1.0f, tm.offsetBodyX, tm.offsetBodyY);
    tanks[1] = new Tank(256, 0, 100, new float[3] { 0.0f, 0.8f, 0.0f }, M_PI_4, 0.01f, 0.5f, 3.0f, -1.0f, tm.offsetBodyX, tm.offsetBodyY);

    while (!glfwWindowShouldClose(window))
    {   
        glfwPollEvents();
        states[0] = glfwGetKey(window, GLFW_KEY_A);
        states[1] = glfwGetKey(window, GLFW_KEY_D);
        states[2] = glfwGetKey(window, GLFW_KEY_W);
        states[3] = glfwGetKey(window, GLFW_KEY_S);
        // states[4] = glfwGetKey(window, GLFW_KEY_LEFT);
        // states[5] = glfwGetKey(window, GLFW_KEY_RIGHT);
        // states[6] = glfwGetKey(window, GLFW_KEY_UP);
        // states[7] = glfwGetKey(window, GLFW_KEY_DOWN);
        states[4] = glfwGetKey(window, GLFW_KEY_Q);
        states[5] = glfwGetKey(window, GLFW_KEY_E);
        states[6] = glfwGetKey(window, GLFW_KEY_SPACE);

        // танк 1
        // влево        
        if (states[0] && !states[1])
        {
            tanks[0]->Rotate(1);
        }
        // вправо 
        if (!states[0] && states[1])
        {
            tanks[0]->Rotate(-1);
        }
        // вперёд
        if (states[2] && !states[3])
        {
            tanks[0]->moveDir = 1;
        }   
        // вниз
        if (!states[2] && states[3])
        {
            tanks[0]->moveDir = -1;
        }

        // поворот башни влево
        if (states[4] && !states[5])
        {
            tanks[0]->tower->Rotate(1);
        }

        // поворот башни вправо
        if (!states[4] && states[5])
        {
            tanks[0]->tower->Rotate(-1);
        }

        if (states[6])
        {
            GunShell* gs = tanks[0]->Shoot();
            if (gs)
            {
                gsCollection->Add(gs);
            }
        }

        if (glfwGetKey(window, GLFW_KEY_UP))
        {
            GunShell* gs = tanks[1]->Shoot();
            if (gs)
            {
                gsCollection->Add(gs);
            }
        }

        tanks[0]->Move();
        tanks[1]->Move();
        Object* iter = gsCollection->first;
        while (iter)
        {
            iter->Move();
            iter = iter->next;
        }
        
        // Попадание снаряда в танк!

        // for (unsigned i = 0; i < countShell; i++)
        // {
        //     for (unsigned j = 0; j < countTank; j++)
        //     {
        //         // Написать метод 
        //     }
        // }

        glClearColor(1, 1, 1, 0);
        glClear(GL_COLOR_BUFFER_BIT);

        shdr->Use();
        glUniform2fv(uProj, 1, proj);

        iter = gsCollection->first;
        GunShell* gunShell;
        while(iter)
        {
            gunShell = (GunShell*)iter;
            glUniform3fv(uColor, 1, gunShell->color);
            glUniform2f(uPosition, gunShell->x, gunShell->y);
            glUniform1f(uSize, gunShell->size);
            glUniform1f(uAngle, gunShell->angle);
            glBindVertexArray(ShellVAO);
            glDrawArrays(GL_TRIANGLES, 0, 12);
            iter = iter->next;
        }

        for (int i = 0; i < 2; i++)
        {
            // Draw body
            glUniform3fv(uColor, 1, tanks[i]->color);
            glUniform2f(uPosition, tanks[i]->x, tanks[i]->y);
            glUniform1f(uSize, tanks[i]->size);
            glUniform1f(uAngle, tanks[i]->angle);
            glBindVertexArray(TankVAO);
            glDrawArrays(GL_TRIANGLES, 0, 18);

            // Draw tower
            glUniform3fv(uColor, 1, tanks[i]->color);
            const float tmpX = tanks[i]->tower->bodyOffsetX * cosf(tanks[i]->angle) - tanks[i]->tower->bodyOffsetY * sinf(tanks[i]->angle);
            const float tmpY = tanks[i]->tower->bodyOffsetX * sinf(tanks[i]->angle) + tanks[i]->tower->bodyOffsetY * cosf(tanks[i]->angle);
            glUniform2f(uPosition, tanks[i]->x + tmpX, 
                tanks[i]->y + tmpY
            );

            glUniform1f(uSize, tanks[i]->size);
            glUniform1f(uAngle, tanks[i]->tower->angle);
            glDrawArrays(GL_TRIANGLES, 18, 12);
        }
        glBindVertexArray(0);

        glfwSwapBuffers(window);
    }

    glDeleteVertexArrays(1, &TankVAO);
    glDeleteBuffers(1, &TankVBO);
    glDeleteVertexArrays(1, &ShellVAO);
    glDeleteBuffers(1, &ShellVBO);
    glfwTerminate();

    return 0;
}