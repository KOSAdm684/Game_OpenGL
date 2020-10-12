#include "BaseControl.h"
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <iostream>
#include <string.h>
#include <vector>
#include "FileViewerItem.h"
#include "../Controls/Button.h"
#include "../Controls/Label.h"
#include "../BusinessLogic/DirectoryReader.h"


#ifndef FILEVIEWER_H
#define FILEVIEWER_H

class FileViewer : public BaseControl
{

private:
  double offset = 0;
  void addOffset();
  void subtractOffset();
  void GoBack();

public:
  std::wstring path;
  std::wstring selpath;
  std::wstring selName;
  bool refresh;

  float* GetVertices(int &count);
  std::vector<FileItemInfo> items;
  std::vector<FileViewerItem> buttons;
  Label name;
  Label lpath;
  Label lpath2;
  Label size;
  Label type;
  Label background;
  Button up;
  Button down;
  Button back;

  double GetOffset();
  bool Scrolling(double x, double y, bool mouse);
  void CheckItems(int x, int y, bool mouse_left);
  void CheckBack(double x, double y);
  void Show(std::wstring path);

  // constractor
  FileViewer(float Width, float Height, float PosX, float PosY);
};

#endif
