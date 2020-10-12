#include "Button.h"
#include "Label.h"

#ifndef FILEVIEWERITEM_H
#define FILEVIEWERITEM_H

const float COLOR_STATE2[][3]{
  {0.2f, 0.2f, 0.2f},
  {0.5f, 0.5f, 0.5f},
  {0.8f, 0.8f, 0.8f}
};

class FileViewerItem : public Button
{

private:

  void(*onClick)();

public:

  float* GetColor();
  Label name;
  Label size;
  Label type;
  ButtonState state;

  void ButtonHandler(int x, int y, bool mouse_left);
  void CheckClick(int x, int y);
  // constractor
  FileViewerItem(float Width, float Height, float PosX, float PosY, std::wstring l1, std::wstring l2, std::wstring l3);
  FileViewerItem();
};

#endif
