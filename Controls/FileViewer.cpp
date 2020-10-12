#include "FileViewer.h"
#include <unistd.h>

// constractor
FileViewer::FileViewer(float Width, float Height, float PosX, float PosY):
BaseControl(Width, Height, PosX, PosY)
{
  back.SetWidth(48);
  back.SetHeight(28);
  back.SetPosX(PosX + 1);
  back.SetPosY(PosY - 1);
  back.Content = L"Back";

  lpath.SetWidth(105);
  lpath.SetHeight(28);
  lpath.SetPosX(back.GetPosX() + 1 + back.GetWidth());
  lpath.SetPosY(PosY - 1);
  lpath.fontColor[0] = 0;
  lpath.fontColor[1] = 0;
  lpath.fontColor[2] = 0;
  lpath.Content = L"Current path:";

  lpath2.SetWidth(Width - 4 - lpath.GetWidth() - back.GetWidth());
  lpath2.SetHeight(28);
  lpath2.SetPosX(lpath.GetPosX() + lpath.GetWidth() + 1);
  lpath2.SetPosY(lpath.GetPosY());
  lpath2.fontColor[0] = 0;
  lpath2.fontColor[1] = 0;
  lpath2.fontColor[2] = 0;
  lpath2.Content = path;

  name.SetWidth(Width / 3 - 1);
  name.SetHeight(30);
  name.SetPosX(PosX + 1);
  name.SetPosY(lpath.GetPosY() - lpath.GetHeight() - 1);
  name.fontColor[0] = 0;
  name.fontColor[1] = 0;
  name.fontColor[2] = 0;
  name.Content = L"Name";

  size.SetWidth(Width / 3 - 2);
  size.SetHeight(30);
  size.SetPosX(name.GetPosX() + name.GetWidth() + 1);
  size.SetPosY(name.GetPosY());
  size.fontColor[0] = 0;
  size.fontColor[1] = 0;
  size.fontColor[2] = 0;
  size.Content = L"Size";

  type.SetWidth(Width / 3 - 1);
  type.SetHeight(30);
  type.SetPosX(size.GetPosX() + size.GetWidth() + 1);
  type.SetPosY(size.GetPosY());
  type.fontColor[0] = 0;
  type.fontColor[1] = 0;
  type.fontColor[2] = 0;
  type.Content = L"Type";

  up.SetWidth(20);
  up.SetHeight(30);
  up.SetPosX(PosX + Width - 21);
  up.SetPosY(PosY - name.GetHeight() - lpath.GetHeight() - 3);
  //up.SetMethod(addOffset);
  up.Content = L"Up";

  down.SetWidth(20);
  down.SetHeight(30);
  down.SetPosX(PosX + Width - 21);
  down.SetPosY(PosY - Height + 31);
  down.Content = L"D";

  background.SetWidth(Width - 2 - up.GetWidth());
  background.SetHeight(Height - name.GetHeight() - lpath.GetHeight() - 4);
  background.SetPosX(name.GetPosX());
  background.SetPosY(name.GetPosY() - name.GetHeight() - 1);// - name.GetHeight() - lpath.GetHeight() - background.GetHeight() - 3);

  refresh = false;
  selpath = path;

  Show(L"/");
}

bool FileViewer::Scrolling(double x, double y, bool mouse){
  up.ButtonHandler((int)x, (int)y, mouse);
  if(up.state == ACTIVE){
    subtractOffset();
    return true;
  }
  down.ButtonHandler((int)x, (int)y, mouse);
  if(down.state == ACTIVE){
    addOffset();
    return true;
  }
  back.ButtonHandler((int)x, (int)y, mouse);

  return false;
}

void FileViewer::CheckBack(double x, double y){
  if(x >= back.GetPosX() && x <= back.GetPosX() + back.GetWidth()){
    if(y <= back.GetPosY() && y >= back.GetPosY() - back.GetHeight()){
      GoBack();
    }
  }
}

void FileViewer::GoBack(){
  if(path.compare(L"/")){
    std::wstring::size_type len = path.find_last_of(L"/\\");
    if(len == 0){
      len += 1;
    }
    path = path.substr(0, len);
    Show(path);
  }
}

void FileViewer::CheckItems(int x, int y, bool mouse_left){
  float scl = background.GetHeight() * offset / 2;
  int i = 0;
  bool c = false;
  float upY = background.GetHeight() / 2;
  float downY = -upY;
  for(i = 0; i < buttons.size(); i++){
      if(x >= buttons[i].GetPosX() && x <= buttons[i].GetPosX() + buttons[i].GetWidth() ){
        if(y >= downY && y <= upY){
          if(y <= buttons[i].GetPosY() + scl && y >= buttons[i].GetPosY() - buttons[i].GetHeight() + scl){
            if(mouse_left){
              std::wstring s(buttons[i].name.Content);
              std::wstring p;

              if(wcscmp(path.c_str(), L"/") != 0){
                  p = path + L'/' + s;
              }
              else{
                  p = path + s;
              }

              if(buttons[i].type.Content.compare(L"File")){
                Show(p);
                selpath = p;
                return;
                //buttons[i].state = INACTIVE;
                //printf("%d", i);
              }
              else{
                //selpath = p;
                selName = s;
              }
            }
          }
        }
      }
  }
}

float Calculate(float a, int b){
    float res = a / b;
    res *= 2;
    return res;
}

float* FileViewer::GetVertices(int &count){
    float *vertices = new float[400];
    count = 0;
    float Height = background.GetHeight();
    float Width = background.GetWidth();
    float up = Height / 2;
    float down = -Height / 2;
    for (int i = 0; i < buttons.size(); i++) {
        float posX = buttons[i].GetPosX();
        float posY = buttons[i].GetPosY();
        float width = buttons[i].GetWidth();
        float height = buttons[i].GetHeight();
        if(posY + background.GetHeight() * offset / 2 >= down && posY - height + background.GetHeight() * offset / 2 <= up){
          //printf("%d\n", i);

          vertices[count++] = Calculate(posX, Width);
          vertices[count++] = Calculate(posY, Height);
          vertices[count++] = Calculate(posX + width, Width);
          vertices[count++] = Calculate(posY, Height);
          vertices[count++] = Calculate(posX, Width);
          vertices[count++] = Calculate(posY - height, Height);

          vertices[count++] = Calculate(posX, Width);
          vertices[count++] = Calculate(posY - height, Height);
          vertices[count++] = Calculate(posX + width, Width);
          vertices[count++] = Calculate(posY - height, Height);
          vertices[count++] = Calculate(posX + width, Width);
          vertices[count++] = Calculate(posY, Height);

        }
    }
    //printf("%d\n", count);
    return vertices;
}

double FileViewer::GetOffset(){
  return offset;
}

void FileViewer::addOffset(){
  float totalHeight = items.size() * 31 + 1;
  float down = -background.GetHeight() / 2;
  //lastY - 31 + background.GetHeight() * x / 2 = down;
  //background.GetHeight() * x / 2 = -lastY + 31 + down;
  float x = 2*(-((background.GetHeight() / 2) - totalHeight) + down) / background.GetHeight();
  if ((x - offset) >= 0.05){
      offset += 0.05;
  }

}

void FileViewer::subtractOffset(){
  if(offset <= 0.05) {
    offset = 0.f;
  }
  else {
    offset -= 0.05;
  }
}

void FileViewer::Show(std::wstring myPath){
  // setting fileviewer path current
  lpath2.Content = myPath;
  offset = 0;
  items.clear();

  DirectoryReader reader(myPath);
  path = reader.Read(items);

  buttons.clear();

  for(int i = 0; i < items.size(); i++){
    if(i == 0){
      std::wstring type = items[i].type == 0 ? L"File" : L"Folder";
      std::wstring fSize = std::to_wstring(items[i].size);
      FileViewerItem b(GetWidth(), 30.0, - background.GetWidth() / 2, background.GetHeight() / 2, items[i].name, fSize, type);
      buttons.push_back(b);
    }
    else{
      std::wstring type = items[i].type == 0 ? L"File" : L"Folder";
      std::wstring fSize = std::to_wstring(items[i].size);
      FileViewerItem b(GetWidth(), 30.0, buttons[i - 1].GetPosX(), buttons[i - 1].GetPosY() - 31.0, items[i].name, fSize, type);
      buttons.push_back(b);
    }
  }

  // refreshes fv items to draw
  refresh = true;
}
