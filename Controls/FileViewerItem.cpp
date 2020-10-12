#include "FileViewerItem.h"


void FileViewerItem::ButtonHandler(int x, int y, bool mouse_left){
  if(x >= this->GetPosX() && x <= this->GetPosX() + this->GetWidth()){
    if(y <= this->GetPosY() && y >= this->GetPosY() - this->GetHeight()){
      if(mouse_left){
        state = ACTIVE;
      }
      else if(state == ACTIVE){
        ((void(*)())onClick)();
        state = INACTIVE;
      }
      else{
        state = HOVER;
      }
    }
    else{
      state = INACTIVE;
    }
  }
  else{
    state = INACTIVE;
  }
}


float* FileViewerItem::GetColor(){
  return new float[3]{
    COLOR_STATE2[state][0],
    COLOR_STATE2[state][1],
    COLOR_STATE2[state][2]
  };
}

// constractor
FileViewerItem::FileViewerItem(float Width, float Height, float PosX, float PosY, std::wstring l1, std::wstring l2, std::wstring l3):
Button(Width - 21, Height, PosX, PosY)
{
  this->name.Content = l1;
  this->name.SetPosX(PosX);
  this->name.SetPosY(PosY);
  this->name.SetWidth(Width / 3 - 4);
  this->name.SetHeight(Height);
  this->size.Content = l2;
  this->size.SetPosX(name.GetPosX() + name.GetWidth() + 2);
  this->size.SetPosY(PosY);
  this->size.SetWidth(Width / 3 - 4);
  this->size.SetHeight(Height);
  this->type.Content = l3;
  this->type.SetPosX(size.GetPosX() + size.GetWidth() + 2);
  this->type.SetPosY(PosY);
  this->type.SetWidth(Width / 3 - 24);
  this->type.SetHeight(Height);
}

FileViewerItem::FileViewerItem():
Button()
{
}
