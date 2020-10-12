#include "Button.h"


void Button::Draw(){

}

void Button::ButtonHandler(int x, int y, bool mouse_left){
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
/*
void Button::CheckClick(int x, int y){
  if(x >= PosX && x <= PosX + Width && y >= PosY && y <= PosY + Height)
    ((void(*)())onClick)();
}*/


float* Button::GetColor(){
  return new float[3]{
    COLOR_STATE[state][0],
    COLOR_STATE[state][1],
    COLOR_STATE[state][2]
  };
}

// constractor
Button::Button(float Width, float Height, float PosX, float PosY, void(*f)(), std::wstring Content):
BaseControl(Width, Height, PosX, PosY, Content)
{
  this->onClick = f;
  this->state = INACTIVE;
}

void empty(){}

// constractor
Button::Button(float Width, float Height, float PosX, float PosY):
BaseControl(Width, Height, PosX, PosY)
{
  this->state = INACTIVE;
  this->onClick = empty;
}

Button::Button():
BaseControl(0, 0, 0, 0, L"")
{
  this->onClick = empty;
  this->state = INACTIVE;
}

Button::Button(void(*f)()):
BaseControl(0, 0, 0, 0, L"")
{
  this->onClick = f;
  this->state = INACTIVE;
}
