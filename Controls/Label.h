#include "BaseControl.h"
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <iostream>
#include <string.h>

#ifndef LABEL_H
#define LABEL_H

class Label : public BaseControl
{

public:
  float fontColor[3];
  float background[3];

  // constractor
  Label(float Width, float Height, float PosX, float PosY, float font[3], float back[3], std::wstring Content);
  Label();

};

#endif
