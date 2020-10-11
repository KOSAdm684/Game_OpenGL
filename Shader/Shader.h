#include <GL/glew.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>

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
