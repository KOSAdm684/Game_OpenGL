#include "Label.h"

// constractor
Label::Label(float Width, float Height, float PosX, float PosY, float font[3], float back[3], std::wstring Content):
BaseControl(Width, Height, PosX, PosY, Content)
{
    this->fontColor[0] = font[0];
    this->fontColor[1] = font[1];
    this->fontColor[2] = font[2];

    this->background[0] = back[0];
    this->background[1] = back[1];
    this->background[2] = back[2];
}

Label::Label():
BaseControl(0, 0, 0, 0, L"")
{
}
