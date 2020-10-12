#include "Display.h"

Display::Display(GLuint width, GLuint height, const char* title, GLFWkeyfun keycallback, GLFWmousebuttonfun mousecallback)
{
       //  Initialize GLFW and setup window config
       glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
       glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
       glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_ANY_PROFILE);
       glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

       // Create a GLFWwindow
       window = glfwCreateWindow(width, height, title, nullptr, nullptr);
       if (!window) {
           std::cout << "Could not initialize window.";
           std::cin.get();
           exit(1);
       }
       glfwMakeContextCurrent(window);

       // Set the required callback functions
       glfwSetKeyCallback(window, keycallback);
       glfwSetMouseButtonCallback(window, mousecallback);

       // Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
       glewExperimental = GL_TRUE;

       // Set Viewport to fill window
       glViewport(0, 0, width, height);
}

Display::~Display() {
       //glfwTerminate();
}

void Display::Update(bool draw, bool pollevents) {
       //  Update Display
       if (draw) {
           glfwSwapBuffers(window);
       }

       //  Check for key press etc.
       if (pollevents) {
           glfwPollEvents();
       }

}

float* Display::GetVertices(int Width, int Height, int &count){
    float *vertices = new float[300];

    count = 0;
    for (int i = 0; i < buttons.size(); i++) {
        float posX = buttons[i].GetPosX();
        float posY = buttons[i].GetPosY();
        float width = buttons[i].GetWidth();
        float height = buttons[i].GetHeight();
        vertices[count++] = Display::Calculate(posX, Width);
        vertices[count++] = Display::Calculate(posY, Height);
        vertices[count++] = Display::Calculate(posX + width, Width);
        vertices[count++] = Display::Calculate(posY, Height);
        vertices[count++] = Display::Calculate(posX, Width);
        vertices[count++] = Display::Calculate(posY - height, Height);

        vertices[count++] = Display::Calculate(posX, Width);
        vertices[count++] = Display::Calculate(posY - height, Height);
        vertices[count++] = Display::Calculate(posX + width, Width);
        vertices[count++] = Display::Calculate(posY - height, Height);
        vertices[count++] = Display::Calculate(posX + width, Width);
        vertices[count++] = Display::Calculate(posY, Height);
      }

      for (int i = 0; i < labels.size(); i++) {
          float posX = labels[i].GetPosX();
          float posY = labels[i].GetPosY();
          float width = labels[i].GetWidth();
          float height = labels[i].GetHeight();
          vertices[count++] = Display::Calculate(posX, Width);
          vertices[count++] = Display::Calculate(posY, Height);
          vertices[count++] = Display::Calculate(posX + width, Width);
          vertices[count++] = Display::Calculate(posY, Height);
          vertices[count++] = Display::Calculate(posX, Width);
          vertices[count++] = Display::Calculate(posY - height, Height);

          vertices[count++] = Display::Calculate(posX, Width);
          vertices[count++] = Display::Calculate(posY - height, Height);
          vertices[count++] = Display::Calculate(posX + width, Width);
          vertices[count++] = Display::Calculate(posY - height, Height);
          vertices[count++] = Display::Calculate(posX + width, Width);
          vertices[count++] = Display::Calculate(posY, Height);
      }

      float posX = fv->GetPosX();
      float posY = fv->GetPosY();
      float width = fv->GetWidth();
      float height = fv->GetHeight();
      vertices[count++] = Display::Calculate(posX, Width);
      vertices[count++] = Display::Calculate(posY, Height);
      vertices[count++] = Display::Calculate(posX + width, Width);
      vertices[count++] = Display::Calculate(posY, Height);
      vertices[count++] = Display::Calculate(posX, Width);
      vertices[count++] = Display::Calculate(posY - height, Height);

      vertices[count++] = Display::Calculate(posX, Width);
      vertices[count++] = Display::Calculate(posY - height, Height);
      vertices[count++] = Display::Calculate(posX + width, Width);
      vertices[count++] = Display::Calculate(posY - height, Height);
      vertices[count++] = Display::Calculate(posX + width, Width);
      vertices[count++] = Display::Calculate(posY, Height);

      posX = fv->up.GetPosX();
      posY = fv->up.GetPosY();
      width = fv->up.GetWidth();
      height = fv->up.GetHeight();
      vertices[count++] = Display::Calculate(posX, Width);
      vertices[count++] = Display::Calculate(posY, Height);
      vertices[count++] = Display::Calculate(posX + width, Width);
      vertices[count++] = Display::Calculate(posY, Height);
      vertices[count++] = Display::Calculate(posX, Width);
      vertices[count++] = Display::Calculate(posY - height, Height);

      vertices[count++] = Display::Calculate(posX, Width);
      vertices[count++] = Display::Calculate(posY - height, Height);
      vertices[count++] = Display::Calculate(posX + width, Width);
      vertices[count++] = Display::Calculate(posY - height, Height);
      vertices[count++] = Display::Calculate(posX + width, Width);
      vertices[count++] = Display::Calculate(posY, Height);

      posX = fv->down.GetPosX();
      posY = fv->down.GetPosY();
      width = fv->down.GetWidth();
      height = fv->down.GetHeight();
      vertices[count++] = Display::Calculate(posX, Width);
      vertices[count++] = Display::Calculate(posY, Height);
      vertices[count++] = Display::Calculate(posX + width, Width);
      vertices[count++] = Display::Calculate(posY, Height);
      vertices[count++] = Display::Calculate(posX, Width);
      vertices[count++] = Display::Calculate(posY - height, Height);

      vertices[count++] = Display::Calculate(posX, Width);
      vertices[count++] = Display::Calculate(posY - height, Height);
      vertices[count++] = Display::Calculate(posX + width, Width);
      vertices[count++] = Display::Calculate(posY - height, Height);
      vertices[count++] = Display::Calculate(posX + width, Width);
      vertices[count++] = Display::Calculate(posY, Height);

      posX = fv->back.GetPosX();
      posY = fv->back.GetPosY();
      width = fv->back.GetWidth();
      height = fv->back.GetHeight();
      vertices[count++] = Display::Calculate(posX, Width);
      vertices[count++] = Display::Calculate(posY, Height);
      vertices[count++] = Display::Calculate(posX + width, Width);
      vertices[count++] = Display::Calculate(posY, Height);
      vertices[count++] = Display::Calculate(posX, Width);
      vertices[count++] = Display::Calculate(posY - height, Height);

      vertices[count++] = Display::Calculate(posX, Width);
      vertices[count++] = Display::Calculate(posY - height, Height);
      vertices[count++] = Display::Calculate(posX + width, Width);
      vertices[count++] = Display::Calculate(posY - height, Height);
      vertices[count++] = Display::Calculate(posX + width, Width);
      vertices[count++] = Display::Calculate(posY, Height);

      posX = fv->lpath.GetPosX();
      posY = fv->lpath.GetPosY();
      width = fv->lpath.GetWidth();
      height = fv->lpath.GetHeight();
      vertices[count++] = Display::Calculate(posX, Width);
      vertices[count++] = Display::Calculate(posY, Height);
      vertices[count++] = Display::Calculate(posX + width, Width);
      vertices[count++] = Display::Calculate(posY, Height);
      vertices[count++] = Display::Calculate(posX, Width);
      vertices[count++] = Display::Calculate(posY - height, Height);

      vertices[count++] = Display::Calculate(posX, Width);
      vertices[count++] = Display::Calculate(posY - height, Height);
      vertices[count++] = Display::Calculate(posX + width, Width);
      vertices[count++] = Display::Calculate(posY - height, Height);
      vertices[count++] = Display::Calculate(posX + width, Width);
      vertices[count++] = Display::Calculate(posY, Height);

      posX = fv->lpath2.GetPosX();
      posY = fv->lpath2.GetPosY();
      width = fv->lpath2.GetWidth();
      height = fv->lpath2.GetHeight();
      vertices[count++] = Display::Calculate(posX, Width);
      vertices[count++] = Display::Calculate(posY, Height);
      vertices[count++] = Display::Calculate(posX + width, Width);
      vertices[count++] = Display::Calculate(posY, Height);
      vertices[count++] = Display::Calculate(posX, Width);
      vertices[count++] = Display::Calculate(posY - height, Height);

      vertices[count++] = Display::Calculate(posX, Width);
      vertices[count++] = Display::Calculate(posY - height, Height);
      vertices[count++] = Display::Calculate(posX + width, Width);
      vertices[count++] = Display::Calculate(posY - height, Height);
      vertices[count++] = Display::Calculate(posX + width, Width);
      vertices[count++] = Display::Calculate(posY, Height);

      posX = fv->name.GetPosX();
      posY = fv->name.GetPosY();
      width = fv->name.GetWidth();
      height = fv->name.GetHeight();
      vertices[count++] = Display::Calculate(posX, Width);
      vertices[count++] = Display::Calculate(posY, Height);
      vertices[count++] = Display::Calculate(posX + width, Width);
      vertices[count++] = Display::Calculate(posY, Height);
      vertices[count++] = Display::Calculate(posX, Width);
      vertices[count++] = Display::Calculate(posY - height, Height);

      vertices[count++] = Display::Calculate(posX, Width);
      vertices[count++] = Display::Calculate(posY - height, Height);
      vertices[count++] = Display::Calculate(posX + width, Width);
      vertices[count++] = Display::Calculate(posY - height, Height);
      vertices[count++] = Display::Calculate(posX + width, Width);
      vertices[count++] = Display::Calculate(posY, Height);

      posX = fv->size.GetPosX();
      posY = fv->size.GetPosY();
      width = fv->size.GetWidth();
      height = fv->size.GetHeight();
      vertices[count++] = Display::Calculate(posX, Width);
      vertices[count++] = Display::Calculate(posY, Height);
      vertices[count++] = Display::Calculate(posX + width, Width);
      vertices[count++] = Display::Calculate(posY, Height);
      vertices[count++] = Display::Calculate(posX, Width);
      vertices[count++] = Display::Calculate(posY - height, Height);

      vertices[count++] = Display::Calculate(posX, Width);
      vertices[count++] = Display::Calculate(posY - height, Height);
      vertices[count++] = Display::Calculate(posX + width, Width);
      vertices[count++] = Display::Calculate(posY - height, Height);
      vertices[count++] = Display::Calculate(posX + width, Width);
      vertices[count++] = Display::Calculate(posY, Height);

      posX = fv->type.GetPosX();
      posY = fv->type.GetPosY();
      width = fv->type.GetWidth();
      height = fv->type.GetHeight();
      vertices[count++] = Display::Calculate(posX, Width);
      vertices[count++] = Display::Calculate(posY, Height);
      vertices[count++] = Display::Calculate(posX + width, Width);
      vertices[count++] = Display::Calculate(posY, Height);
      vertices[count++] = Display::Calculate(posX, Width);
      vertices[count++] = Display::Calculate(posY - height, Height);

      vertices[count++] = Display::Calculate(posX, Width);
      vertices[count++] = Display::Calculate(posY - height, Height);
      vertices[count++] = Display::Calculate(posX + width, Width);
      vertices[count++] = Display::Calculate(posY - height, Height);
      vertices[count++] = Display::Calculate(posX + width, Width);
      vertices[count++] = Display::Calculate(posY, Height);

      posX = fv->background.GetPosX();
      posY = fv->background.GetPosY();
      width = fv->background.GetWidth();
      height = fv->background.GetHeight();
      vertices[count++] = Display::Calculate(posX, Width);
      vertices[count++] = Display::Calculate(posY, Height);
      vertices[count++] = Display::Calculate(posX + width, Width);
      vertices[count++] = Display::Calculate(posY, Height);
      vertices[count++] = Display::Calculate(posX, Width);
      vertices[count++] = Display::Calculate(posY - height, Height);

      vertices[count++] = Display::Calculate(posX, Width);
      vertices[count++] = Display::Calculate(posY - height, Height);
      vertices[count++] = Display::Calculate(posX + width, Width);
      vertices[count++] = Display::Calculate(posY - height, Height);
      vertices[count++] = Display::Calculate(posX + width, Width);
      vertices[count++] = Display::Calculate(posY, Height);

/*
      vertices[count++] = Display::Calculate(-width / 2, width);
      vertices[count++] = Display::Calculate(-height/2, height);
      vertices[count++] = Display::Calculate(0, width);
      vertices[count++] = Display::Calculate(0, height);
      vertices[count++] = Display::Calculate(-width/2, width);
      vertices[count++] = Display::Calculate(height / 1.5, height);
*/

      return vertices;
}

float Display::Calculate(float a, int b){
    float res = a / b;
    res *= 2;
    //if(res > 1.f){
    //    res = 1 - res;
    //}

    return res;
}

void Display::Clear(GLfloat r, GLfloat g, GLfloat b, GLfloat a) {
       glClearColor(r, g, b, a);
       glClear(GL_COLOR_BUFFER_BIT);
}

void Display::AddButton(Button b) {
       buttons.push_back(b);
}

void Display::AddLabel(Label l) {
       labels.push_back(l);
}

void Display::CheckButtons(double x, double y, bool mouse_left) {
       for (int i = 0; i < buttons.size(); i++) {
           buttons[i].ButtonHandler((int)x, (int)y, mouse_left);
       }
}
