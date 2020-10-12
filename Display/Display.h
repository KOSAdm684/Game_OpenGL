#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../Controls/Button.h"
#include "../Controls/Label.h"
#include "../Controls/FileViewer.h"
#include <vector>


class Display {
public:
  Display(GLuint width, GLuint height, const char* title, GLFWkeyfun keycallback, GLFWmousebuttonfun mousecallback);
  ~Display();
  GLFWwindow* window;
  std::vector<Button> buttons;
  std::vector<Label> labels;
  FileViewer *fv;
  void Update(bool draw, bool pollevents);
  void Clear(GLfloat r, GLfloat g, GLfloat b, GLfloat a);
  void AddButton(Button b);
  void AddLabel(Label l);
  void CheckButtons(double x, double y, bool mouse_left);
  float* GetVertices(int Width, int Height, int &count);
  float Calculate(float a, int b);
private:
  bool isClosed;
};
