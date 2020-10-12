#include "Shader/Shader.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <ft2build.h>
#include "Display/Display.h"
#include "TextRenderer/TextRenderer.h"

#include FT_FREETYPE_H
#include FT_TRUETYPE_IDS_H

#include <locale>
#include <codecvt>
#include <string>
#include <fstream>

// "костыль", чтобы наш codecvt имел публичный деструктор,
// как того требует wstring_convert
template<class Facet>
struct deletable_facet : Facet
{
    template<class ...Args>
    deletable_facet(Args&& ...args) : Facet(std::forward<Args>(args)...) {}
    ~deletable_facet() {}
};

using namespace std;

bool IsTo;
char From[50];
char To[50];
Display *d;
int width = 640;
int widthHalf = width / 2;
int height = 480;
int heightHalf = height / 2;
Display *mainWindow;
Display *notif;
Shader *textShader;
GLuint VBO, VBO_TEXT, ITEMS_VBO, ITEMS_TEXT_VBO;
GLuint VAO, VAO_TEXT, ITEMS_VAO, ITEMS_TEXT_VAO;
TextRenderer *text;
GLuint u_text_screen;
GLuint u_text_width;
GLuint u_text_height;
GLuint u_text_center;
GLuint u_text_color;
GLuint u_text_texture;
GLuint u_text_offset;

Display *Window;


Shader *btn_sh;
GLuint u_btn_offset;
GLuint u_btn_sh_color;
//FileViewer fv(350, 100, -300.0, 150.0);

using convert_type = std::codecvt_utf8<wchar_t>;
std::wstring_convert<convert_type, wchar_t> converter;
void mouseHandler(GLFWwindow * window, int button, int action, int mode);
void mouseHandlerChild(GLFWwindow * window, int button, int action, int mode);
void keyCallback (GLFWwindow * window, int key, int scancode, int action, int mode);
void reshape ( GLFWwindow * window, int w, int h );
void func2();
void openNewWindow();
void func();
void print(Button &b);
void printLabel(Label &l);
void printLabel2(Label &l);
void select();
void notification();

void fillBuffer();

void select(){
  if(IsTo){
    if(Window->fv->selpath.length() != 0){
      mainWindow->labels[5].Content = Window->fv->selpath;
    }
  }
  else{
    if(Window->fv->selpath.length() != 0){
      mainWindow->labels[1].Content = Window->fv->selName;
      std::wstring FromS = Window->fv->selpath + L"/" + Window->fv->selName;
      mainWindow->labels[3].Content = Window->fv->selpath;

      std::string pathString = converter.to_bytes(FromS.c_str());
      strcpy(From, pathString.c_str());
    }
  }
  glfwSetWindowShouldClose (Window->window, 1);
}

void f1(){
  IsTo = false;
  func();
}

void f2(){
  IsTo = true;
  func();
}

void copy(){
  if(mainWindow->labels[5].Content.length() != 0 && mainWindow->labels[1].Content.length() != 0){
    std::wstring ToS = mainWindow->labels[5].Content + L"/" + mainWindow->labels[1].Content;
    std::string pathString = converter.to_bytes(ToS.c_str());
    strcpy(To, pathString.c_str());

    std::ifstream src(From, std::ios::binary);
    std::ofstream dest(To, std::ios::binary);
    dest << src.rdbuf();

    mainWindow->labels[1].Content = L"";
    mainWindow->labels[3].Content = L"";
    mainWindow->labels[5].Content = L"";

    cout << "Ok";
    //notification();
  }
}

void func(){
  //glfwInit();
  //pid_t pid = fork();
  //if(pid < 0){
  //  printf("Err");
  //}
  //else if(pid == 0){
  //  printf("child");

    GLuint VBO2, VBO_TEXT2, ITEMS_VBO2, ITEMS_TEXT_VBO2;
    GLuint VAO2, VAO_TEXT2, ITEMS_VAO2, ITEMS_TEXT_VAO2;
    Window = new Display(width, height, "OpenFileDialog", keyCallback, mouseHandlerChild);

    //glewInit();

    Button b1(150, 30, -75.0, -150.0, select, L"Ok");

    float c[3] = { 0.f, 0.f, 0.f };

    FileViewer fv(width - 50, 280, -300.0, 200.0);

    Window->fv = &fv;
    Window->AddButton(b1);
    //Window->AddButton(b2);

    Shader *btn_sh2 = new Shader("Shaders/btn_shader.vert", "Shaders/btn_shader.frag");

    GLuint program = btn_sh2->Program;

    GLuint u_btn_sh_color2 = glGetUniformLocation(program, "u_color");
    GLuint u_btn_offset2 = glGetUniformLocation(program, "u_offset");

    Shader *textShader2 = new Shader("Shaders/TextShader.vert", "Shaders/TextShader.frag");

    program = textShader2->Program;
    GLuint u_text_screen2 = glGetUniformLocation(program, "u_screen");
    GLuint u_text_width2 = glGetUniformLocation(program, "u_width");
    GLuint u_text_height2 = glGetUniformLocation(program, "u_height");
    GLuint u_text_center2 = glGetUniformLocation(program, "u_center");
    GLuint u_text_color2 = glGetUniformLocation(program, "u_color");
    GLuint u_text_texture2 = glGetUniformLocation(program, "u_texture");
    GLuint u_text_offset2 = glGetUniformLocation(program, "u_offset");

    TextRenderer *text2 = new TextRenderer(18, "Types/times_new_roman.ttf", 0);

    glGenBuffers(1, &VBO2);
    glGenBuffers(1, &VBO_TEXT2);
    glGenBuffers(1, &ITEMS_VBO2);
    glGenBuffers(1, &ITEMS_TEXT_VBO2);


    glGenVertexArrays(1, &VAO2);
    glGenVertexArrays(1, &VAO_TEXT2);
    glGenVertexArrays(1, &ITEMS_VAO2);
    glGenVertexArrays(1, &ITEMS_TEXT_VAO2);

    glBindVertexArray(ITEMS_TEXT_VAO2);
    glBindBuffer(GL_ARRAY_BUFFER, ITEMS_TEXT_VBO2);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(VAO_TEXT2);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_TEXT2);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

  //
    glBindVertexArray(ITEMS_VAO2);

    int countItems;
    float scale =  fv.background.GetHeight() * 0.05;
    float *verticesItems = fv.GetVertices(countItems);
    //float *verticesItems = mainWindow->GetVertices(width, height, countItems);

    glBindBuffer(GL_ARRAY_BUFFER, ITEMS_VBO2);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 400, verticesItems, GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
    glEnableVertexAttribArray(0);
  //
    glBindVertexArray(VAO2);
    int count;
    float *vertices = Window->GetVertices(width, height, count);

    glBindBuffer(GL_ARRAY_BUFFER, VBO2);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * count, vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
    glEnableVertexAttribArray(0);

    double xpos, ypos;
    bool mouse_left;

    count = Window->buttons.size();
    int count2 = Window->labels.size();
    count2 += count;
    glUniform1f(u_btn_offset2, 0);

    wstring path2(fv.path.begin(), fv.path.end());
    fv.lpath2.Content = path2;
    while (!glfwWindowShouldClose(Window->window))
    {
      glfwGetCursorPos(Window->window, &xpos, &ypos);
      mouse_left = glfwGetMouseButton(Window->window, GLFW_MOUSE_BUTTON_LEFT);

      Window->CheckButtons(xpos - widthHalf, heightHalf - ypos, mouse_left);
      //mainWindow->fv->CheckItems(xpos - 20 - mainWindow->fv->background.GetWidth() / 2, (mainWindow->fv->background.GetHeight() / 2) - (ypos - 213), mouse_left);

      if(fv.Scrolling(xpos - widthHalf, heightHalf - ypos, mouse_left) || fv.refresh)
      {
        fv.refresh = false;
        glBindBuffer(GL_ARRAY_BUFFER, ITEMS_VBO2);
        vertices = fv.GetVertices(countItems);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float) * countItems, vertices);
        //glBufferData(GL_ARRAY_BUFFER, sizeof(float) * countItems, vertices, GL_DYNAMIC_DRAW);
      }

      Window->Clear(0.2f, 0.3f, 0.3f, 1.0f);
      glBindVertexArray(VAO2);

      btn_sh2->Use();

      for(int i = 0; i < count; i++)
      {
        glUniform3fv(u_btn_sh_color2, 1, Window->buttons[i].GetColor());
        glDrawArrays(GL_TRIANGLES, i * 6, 6);
      }

      for(int i = count; i < count2; i++)
      {
        glUniform3f(u_btn_sh_color2, 1.f, 1.f, 1.f);
        glDrawArrays(GL_TRIANGLES, i * 6, 6);
      }

      //file viewer
      glUniform3f(u_btn_sh_color2, 0.f, 0.f, 0.f);
      glDrawArrays(GL_TRIANGLES, count2 * 6, 6);

      glUniform3fv(u_btn_sh_color2, 1, fv.up.GetColor());
      glDrawArrays(GL_TRIANGLES, (count2 + 1) * 6, 6);

      glUniform3fv(u_btn_sh_color2, 1, fv.down.GetColor());
      glDrawArrays(GL_TRIANGLES, (count2 + 2) * 6, 6);

      glUniform3fv(u_btn_sh_color2, 1, fv.back.GetColor());
      glDrawArrays(GL_TRIANGLES, (count2 + 3) * 6, 6);

      glUniform3f(u_btn_sh_color2, 0.5f, 0.5f, 0.5f);
      glDrawArrays(GL_TRIANGLES, (count2 + 4) * 6, 30);


      glUniform3f(u_btn_sh_color2, 0.f, 0.f, 0.f);
      glDrawArrays(GL_TRIANGLES, (count2 + 9) * 6, 6);

      // background
      glViewport(width / 2 + fv.background.GetPosX(), height / 2 + fv.background.GetPosY() - fv.background.GetHeight(), fv.background.GetWidth(), fv.background.GetHeight());

      glBindVertexArray(ITEMS_VAO2);

      glUniform1f(u_btn_offset2, fv.GetOffset());
      glUniform3f(u_btn_sh_color2, 0.3f, 0.3f, 0.3f);

      glDrawArrays(GL_TRIANGLES, 0, countItems / 2);//6 * fv.buttons.size());
      glUniform1f(u_btn_offset2, 0);

      textShader2->Use();
      glActiveTexture(GL_TEXTURE0);

      glEnable(GL_BLEND);
      glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

      glBindVertexArray(ITEMS_TEXT_VAO2);

      glBindBuffer(GL_ARRAY_BUFFER, ITEMS_TEXT_VBO2);

      glUniform1f(u_text_offset2, fv.GetOffset());
      for(int i = 0; i < Window->fv->buttons.size(); ++i)
      {
        printLabel2(Window->fv->buttons[i].name);
        printLabel2(Window->fv->buttons[i].size);
        printLabel2(Window->fv->buttons[i].type);
      }

      glViewport ( 0, 0, width, height);


      glBindVertexArray(VAO_TEXT2);

      glBindBuffer(GL_ARRAY_BUFFER, VBO_TEXT2);
      glUniform1f(u_text_offset, 0);

      for(unsigned int i = 0; i < count; ++i)
      {
        print(Window->buttons[i]);
      }

      for(unsigned int i = 0; i < Window->labels.size(); ++i)
      {
        printLabel(Window->labels[i]);
      }

      printLabel(Window->fv->name);
      printLabel(Window->fv->size);
      printLabel(Window->fv->type);
      printLabel(Window->fv->lpath);
      print(Window->fv->back);
      printLabel(Window->fv->lpath2);

      glDisable(GL_BLEND);

      glActiveTexture(0);

      Window->Update(true, true);
      usleep(16);
    }

    glDeleteBuffers(1, &VBO2);
    glDeleteVertexArrays(1, &VAO2);
    glfwDestroyWindow(Window->window);
    glfwMakeContextCurrent(mainWindow->window);

    //glfwTerminate();

  //}
  //else{
  //  printf("par");
  //}
}

void func2(){
  pid_t p = fork();
  if(p == 0){
    printf("child");
  }
  else if(p > 0){
    printf("parent\n");
  }
  else{
    printf("qweqwe");
  }
  //mainWindow->fv->Show(L"/root/FileCopyApp");
}

void fillBuffer(){

}

void print(Button &b){
  float letterHeight = (float)text->getSymbolHeight();

  glUniform2f(u_text_screen, widthHalf, heightHalf);
  glUniform1f(u_text_height, letterHeight);
  glUniform1i(u_text_texture, 0);


  glUniform3f(u_text_color, 1.f, 1.f, 1.f);

  glUniform1f(u_text_width, text->getTextWidth(b.Content, 1.f));
  glUniform1f(u_text_center, 1.f);
  text->PrintTextToScreen(b.Content, 1.f, b.GetPosX() + b.GetWidth() / 2, b.GetPosY() - b.GetHeight() / 2);
}

void printLabel(Label &l){
  float letterHeight = (float)text->getSymbolHeight();

  glUniform2f(u_text_screen, widthHalf, heightHalf);
  glUniform1f(u_text_height, letterHeight);
  glUniform1i(u_text_texture, 0);


  glUniform3f(u_text_color, l.fontColor[0], l.fontColor[1], l.fontColor[2]);

  glUniform1f(u_text_width, text->getTextWidth(l.Content, 1.f));
  glUniform1f(u_text_center, 0.f);
  text->PrintTextToScreen(l.Content, 1.f, l.GetPosX() + 2, l.GetPosY() - 2 * l.GetHeight() / 3);
}

void printLabel2(Label &l){
  float letterHeight = (float)text->getSymbolHeight();

  glUniform2f(u_text_screen, mainWindow->fv->background.GetWidth() / 2, mainWindow->fv->background.GetHeight() / 2);
  glUniform1f(u_text_height, letterHeight);
  glUniform1i(u_text_texture, 0);


  //glUniform3f(u_text_color, l.fontColor[0], l.fontColor[1], l.fontColor[2]);
  glUniform3f(u_text_color, 1, 1, 1);

  glUniform1f(u_text_width, text->getTextWidth(l.Content, 1.f));
  glUniform1f(u_text_center, 0.f);
  text->PrintTextToScreen(l.Content, 1.f, l.GetPosX() + 2, l.GetPosY() - 2 * l.GetHeight() / 3);
}

void close(){
  glfwSetWindowShouldClose (notif->window, 1);
}

void notification(){
  GLuint VBO3, VBO_TEXT3;
  GLuint VAO3, VAO_TEXT3;
  float w = 200, h = 100;
  cout << "qwe";
  notif = new Display(w, h, "Confirm", keyCallback, mouseHandler);
  cout << "rr";
  //glewInit();

  Button b1(100, 30, -55.0, 0.0, close, L"Ok");

  float c[3] = { 0.f, 0.f, 0.f };

  notif->AddButton(b1);
  //Window->AddButton(b2);

  Shader *btn_sh3 = new Shader("Shaders/btn_shader.vert", "Shaders/btn_shader.frag");

  GLuint program = btn_sh3->Program;

  GLuint u_btn_sh_color3 = glGetUniformLocation(program, "u_color");
  GLuint u_btn_offset3 = glGetUniformLocation(program, "u_offset");

  Shader *textShader3 = new Shader("Shaders/TextShader.vert", "Shaders/TextShader.frag");

  program = textShader3->Program;
  GLuint u_text_screen3 = glGetUniformLocation(program, "u_screen");
  GLuint u_text_width3 = glGetUniformLocation(program, "u_width");
  GLuint u_text_height3 = glGetUniformLocation(program, "u_height");
  GLuint u_text_center3 = glGetUniformLocation(program, "u_center");
  GLuint u_text_color3 = glGetUniformLocation(program, "u_color");
  GLuint u_text_texture3 = glGetUniformLocation(program, "u_texture");
  GLuint u_text_offset3 = glGetUniformLocation(program, "u_offset");

  TextRenderer *text3 = new TextRenderer(18, "Types/times_new_roman.ttf", 0);

  glGenBuffers(1, &VBO3);
  glGenBuffers(1, &VBO_TEXT3);



  glGenVertexArrays(1, &VAO3);
  glGenVertexArrays(1, &VAO_TEXT3);

  glBindVertexArray(VAO_TEXT3);
  glBindBuffer(GL_ARRAY_BUFFER, VBO_TEXT3);
  glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);

  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(0);


  glBindVertexArray(VAO3);
  int count;
  float *vertices = notif->GetVertices(w, h, count);

  glBindBuffer(GL_ARRAY_BUFFER, VBO3);
  glBufferData(GL_ARRAY_BUFFER, sizeof(float) * count, vertices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
  glEnableVertexAttribArray(0);

  double xpos, ypos;
  bool mouse_left;

  count = notif->buttons.size();
  int count2 = notif->labels.size();
  count2 += count;
  glUniform1f(u_btn_offset3, 0);

  while (!glfwWindowShouldClose(notif->window))
  {
    glfwGetCursorPos(notif->window, &xpos, &ypos);
    mouse_left = glfwGetMouseButton(notif->window, GLFW_MOUSE_BUTTON_LEFT);

    notif->CheckButtons(xpos - w / 2, h / 2 - ypos, mouse_left);

    notif->Clear(0.2f, 0.3f, 0.3f, 1.0f);

    glBindVertexArray(VAO3);
    btn_sh3->Use();

    for(int i = 0; i < count; i++)
    {
      glUniform3fv(u_btn_sh_color3, 1, notif->buttons[i].GetColor());
      glDrawArrays(GL_TRIANGLES, i * 6, 6);
    }

    for(int i = count; i < count2; i++)
    {
      glUniform3f(u_btn_sh_color3, 1.f, 1.f, 1.f);
      glDrawArrays(GL_TRIANGLES, i * 6, 6);
    }

    textShader3->Use();
    glActiveTexture(GL_TEXTURE0);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glBindVertexArray(VAO_TEXT3);

    glBindBuffer(GL_ARRAY_BUFFER, VBO_TEXT3);
    glUniform1f(u_text_offset3, 0);

    for(unsigned int i = 0; i < count; ++i)
    {
      print(notif->buttons[i]);
    }

    for(unsigned int i = 0; i < notif->labels.size(); ++i)
    {
      printLabel(notif->labels[i]);
    }
    glDisable(GL_BLEND);

    glActiveTexture(0);

    notif->Update(true, true);
    usleep(16);
  }

  glDeleteBuffers(1, &VBO3);
  glDeleteVertexArrays(1, &VAO3);
  glfwMakeContextCurrent(mainWindow->window);
}

int main(int argc, char** argv)
{
    //pthread_t newThread;
    glfwInit();

    mainWindow = new Display(width, height, "FileCopyApp", keyCallback, mouseHandler);

    glewInit();

    Button b1(150, 30, 30.0, -150.0, f2, L"to");
    Button b2(150, 30, -180.0, -150.0, f1, L"from");
    Button b3(150, 30, -75, 0, copy, L"Copy");

    float c[3] = { 0.f, 0.f, 0.f };
    Label l1(100, 30, -300.0, 200.0, c, c, L"Copy file:");
    Label l2(450, 30, -190.0, 200.0, c, c, L"");
    Label l3(100, 30, -300.0, 150.0, c, c, L"From:");
    Label l4(450, 30, -190.0, 150.0, c, c, L"");
    Label l5(100, 30, -300.0, 100.0, c, c, L"To:");
    Label l6(450, 30, -190.0, 100.0, c, c, L"");

    FileViewer fv(width - 50, 280, -300.0, 90.0);

    mainWindow->fv = &fv;
    mainWindow->AddButton(b1);
    mainWindow->AddButton(b2);
    mainWindow->AddButton(b3);

    mainWindow->AddLabel(l1);
    mainWindow->AddLabel(l2);
    mainWindow->AddLabel(l3);
    mainWindow->AddLabel(l4);
    mainWindow->AddLabel(l5);
    mainWindow->AddLabel(l6);

    btn_sh = new Shader("Shaders/btn_shader.vert", "Shaders/btn_shader.frag");

    GLuint program = btn_sh->Program;

    u_btn_sh_color = glGetUniformLocation(program, "u_color");
    u_btn_offset = glGetUniformLocation(program, "u_offset");

    textShader = new Shader("Shaders/TextShader.vert", "Shaders/TextShader.frag");

    program = textShader->Program;
    u_text_screen = glGetUniformLocation(program, "u_screen");
    u_text_width = glGetUniformLocation(program, "u_width");
    u_text_height = glGetUniformLocation(program, "u_height");
    u_text_center = glGetUniformLocation(program, "u_center");
    u_text_color = glGetUniformLocation(program, "u_color");
    u_text_texture = glGetUniformLocation(program, "u_texture");
    u_text_offset = glGetUniformLocation(program, "u_offset");

    text = new TextRenderer(18, "Types/times_new_roman.ttf", 0);

    glGenBuffers(1, &VBO);
    glGenBuffers(1, &VBO_TEXT);
    glGenBuffers(1, &ITEMS_VBO);
    glGenBuffers(1, &ITEMS_TEXT_VBO);


    glGenVertexArrays(1, &VAO);
    glGenVertexArrays(1, &VAO_TEXT);
    glGenVertexArrays(1, &ITEMS_VAO);
    glGenVertexArrays(1, &ITEMS_TEXT_VAO);

    glBindVertexArray(ITEMS_TEXT_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, ITEMS_TEXT_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(VAO_TEXT);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_TEXT);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

//
    glBindVertexArray(ITEMS_VAO);

    int countItems;
    float scale =  fv.background.GetHeight() * 0.05;
    float *verticesItems = fv.GetVertices(countItems);
    //float *verticesItems = mainWindow->GetVertices(width, height, countItems);

    glBindBuffer(GL_ARRAY_BUFFER, ITEMS_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 400, verticesItems, GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
    glEnableVertexAttribArray(0);
//
    glBindVertexArray(VAO);
    int count;
    float *vertices = mainWindow->GetVertices(width, height, count);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * count, vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
    glEnableVertexAttribArray(0);

    double xpos, ypos;
    bool mouse_left;

    count = mainWindow->buttons.size();
    int count2 = mainWindow->labels.size();
    count2 += count;
    glUniform1f(u_btn_offset, 0);

    wstring path2(fv.path.begin(), fv.path.end());
    fv.lpath2.Content = path2;
    while (!glfwWindowShouldClose(mainWindow->window))
    {
      glfwGetCursorPos(mainWindow->window, &xpos, &ypos);
      mouse_left = glfwGetMouseButton(mainWindow->window, GLFW_MOUSE_BUTTON_LEFT);

      mainWindow->CheckButtons(xpos - widthHalf, heightHalf - ypos, mouse_left);
      //mainWindow->fv->CheckItems(xpos - 20 - mainWindow->fv->background.GetWidth() / 2, (mainWindow->fv->background.GetHeight() / 2) - (ypos - 213), mouse_left);
/*
      if(fv.Scrolling(xpos - widthHalf, heightHalf - ypos, mouse_left) || fv.refresh)
      {
        fv.refresh = false;
        glBindBuffer(GL_ARRAY_BUFFER, ITEMS_VBO);
        //glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(verticesItems), verticesItems);
        printf("Count main %d\n", countItems);
        vertices = fv.GetVertices(countItems);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * countItems, verticesItems, GL_DYNAMIC_DRAW);
      }
*/
      mainWindow->Clear(0.2f, 0.3f, 0.3f, 1.0f);

      glBindVertexArray(VAO);
      btn_sh->Use();

      for(int i = 0; i < count; i++)
      {
        glUniform3fv(u_btn_sh_color, 1, mainWindow->buttons[i].GetColor());
        glDrawArrays(GL_TRIANGLES, i * 6, 6);
      }

      for(int i = count; i < count2; i++)
      {
        glUniform3f(u_btn_sh_color, 1.f, 1.f, 1.f);
        glDrawArrays(GL_TRIANGLES, i * 6, 6);
      }
/*
      //file viewer
      glUniform3f(u_btn_sh_color, 0.f, 0.f, 0.f);
      glDrawArrays(GL_TRIANGLES, count2 * 6, 6);

      glUniform3fv(u_btn_sh_color, 1, fv.up.GetColor());
      glDrawArrays(GL_TRIANGLES, (count2 + 1) * 6, 6);

      glUniform3fv(u_btn_sh_color, 1, fv.down.GetColor());
      glDrawArrays(GL_TRIANGLES, (count2 + 2) * 6, 6);

      glUniform3fv(u_btn_sh_color, 1, fv.back.GetColor());
      glDrawArrays(GL_TRIANGLES, (count2 + 3) * 6, 6);

      glUniform3f(u_btn_sh_color, 0.5f, 0.5f, 0.5f);
      glDrawArrays(GL_TRIANGLES, (count2 + 4) * 6, 30);


      glUniform3f(u_btn_sh_color, 0.f, 0.f, 0.f);
      glDrawArrays(GL_TRIANGLES, (count2 + 9) * 6, 6);

      // background
      glViewport(width / 2 + fv.background.GetPosX(), height / 2 + fv.background.GetPosY() - fv.background.GetHeight(), fv.background.GetWidth(), fv.background.GetHeight());

      glBindVertexArray(ITEMS_VAO);

      glUniform1f(u_btn_offset, fv.GetOffset());
      glUniform3f(u_btn_sh_color, 0.3f, 0.3f, 0.3f);

      glDrawArrays(GL_TRIANGLES, 0, countItems / 2);//6 * fv.buttons.size());
      glUniform1f(u_btn_offset, 0);*/

      textShader->Use();
      glActiveTexture(GL_TEXTURE0);

      glEnable(GL_BLEND);
      glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

      glBindVertexArray(ITEMS_TEXT_VAO);

      glBindBuffer(GL_ARRAY_BUFFER, ITEMS_TEXT_VBO);
      /*
      glUniform1f(u_text_offset, fv.GetOffset());
      for(int i = 0; i < mainWindow->fv->buttons.size(); ++i)
      {
        printLabel2(mainWindow->fv->buttons[i].name);
        printLabel2(mainWindow->fv->buttons[i].size);
        printLabel2(mainWindow->fv->buttons[i].type);
      }

      glViewport ( 0, 0, width, height);
*/

      glBindVertexArray(VAO_TEXT);

      glBindBuffer(GL_ARRAY_BUFFER, VBO_TEXT);
      glUniform1f(u_text_offset, 0);

      for(unsigned int i = 0; i < count; ++i)
      {
        print(mainWindow->buttons[i]);
      }

      for(unsigned int i = 0; i < mainWindow->labels.size(); ++i)
      {
        printLabel(mainWindow->labels[i]);
      }
/*
      printLabel(mainWindow->fv->name);
      printLabel(mainWindow->fv->size);
      printLabel(mainWindow->fv->type);
      printLabel(mainWindow->fv->lpath);
      print(mainWindow->fv->back);
      printLabel(mainWindow->fv->lpath2);
*/
      glDisable(GL_BLEND);

      glActiveTexture(0);

      mainWindow->Update(true, true);
      usleep(16);
    }

    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);
    glfwTerminate();
    return 0;
}

void mouseHandler(GLFWwindow * window, int button, int action, int mode)
{
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    if (action == GLFW_PRESS && button == GLFW_MOUSE_BUTTON_1)
    {
      //mainWindow->fv->CheckBack(xpos - widthHalf, heightHalf - ypos);
      //mainWindow->fv->CheckItems(xpos - 20 - mainWindow->fv->background.GetWidth() / 2, (mainWindow->fv->background.GetHeight() / 2) - (ypos - 213), true);
    }
}

void mouseHandlerChild(GLFWwindow * window, int button, int action, int mode)
{
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    //printf("x=%lf y=%lf\n", xpos, ypos);
    if (action == GLFW_PRESS && button == GLFW_MOUSE_BUTTON_1)
    {
      Window->fv->CheckBack(xpos - widthHalf, heightHalf - ypos);
      Window->fv->CheckItems(xpos - 20 - mainWindow->fv->background.GetWidth() / 2, (mainWindow->fv->background.GetHeight() / 2) - (ypos - 103), true);
  }
}

void keyCallback (GLFWwindow * window, int key, int scancode, int action, int mode)
{
    if(mode == GLFW_MOD_CONTROL && GLFW_KEY_ESCAPE)
      glfwSetWindowShouldClose ( window, GL_TRUE );
}

void reshape ( GLFWwindow * window, int w, int h )
{
    glViewport ( 0, 0, (GLsizei)w, (GLsizei)h);
}
