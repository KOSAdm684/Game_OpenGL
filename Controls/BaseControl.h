#include <GL/freeglut.h>
#include <GL/gl.h>
#include <iostream>
#include <string.h>

#ifndef BASECONTROL_H
#define BASECONTROL_H

class BaseControl
{
  private:
    float Width;
    float Height;
    float PosX;
    float PosY;

  public:
    std::wstring Content;

    float GetWidth();
    float GetHeight();
    float GetPosX();
    float GetPosY();

    void SetWidth(float Width);
    void SetHeight(float height);
    void SetPosX(float PosX);
    void SetPosY(float PosY);

    // constractor
    BaseControl(float Width, float Height, float PosX, float PosY, std::wstring Content);
    BaseControl(float Width, float Height, float PosX, float PosY);

};

#endif
