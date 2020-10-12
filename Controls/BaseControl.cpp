#include "BaseControl.h"

float BaseControl::GetPosY(){
    return PosY;
}

float BaseControl::GetPosX(){
    return PosX;
}

float BaseControl::GetWidth(){
    return Width;

}

float BaseControl::GetHeight(){
    return Height;
}

void BaseControl::SetPosY(float PosY){
    this->PosY = PosY;
}

void BaseControl::SetPosX(float PosX){
    this->PosX = PosX;
}

void BaseControl::SetWidth(float Width){
    this->Width = Width;

}

void BaseControl::SetHeight(float Height){
    this->Height = Height;
}

// constractor
BaseControl::BaseControl(float Width, float Height, float PosX, float PosY, std::wstring Content){
  this->Width = Width;
  this->Height = Height;
  this->PosX = PosX;
  this->PosY = PosY;
  this->Content = Content;
}

// constractor
BaseControl::BaseControl(float Width, float Height, float PosX, float PosY){
  this->Width = Width;
  this->Height = Height;
  this->PosX = PosX;
  this->PosY = PosY;
  this->Content = L"";
}
