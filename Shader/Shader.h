#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
#include <GL/glew.h>

class Shader
{
  private:
    char info_log[512];

  public:
    unsigned Program;

    Shader(const char*, const char*);
    ~Shader();

    char* getInfoLog();
    void Use();
};
