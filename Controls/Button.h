#include "BaseControl.h"

#ifndef BUTTON_H
#define BUTTON_H

enum ButtonState{
  INACTIVE = 0,
  HOVER = 1,
  ACTIVE = 2
};

const float COLOR_STATE[][3]{
  {0.f, 0.f, 0.2f},
  {0.f, 0.f, 0.5f},
  {0.f, 0.f, 1.f}
};

class Button : public BaseControl
{

private:

  void(*onClick)();

public:

  float* GetColor();

  ButtonState state;

  void Draw();
  void ButtonHandler(int x, int y, bool mouse_left);
  void CheckClick(int x, int y);
  // constructor
  Button(float Width, float Height, float PosX, float PosY, void(*f)(), std::wstring Content);
  Button(float Width, float Height, float PosX, float PosY);
  Button();
  Button(void(*f)());


};

#endif
