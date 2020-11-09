#include "Tower.h"

Tower::Tower(float X, float Y, float Angle)
{
    x = X;
    y = Y;
    angle = Angle;
}

void Tower::RotateWithTank(float rot)
{
    angle += rot;
}

void Tower::Move(float spCos, float spSin)
{
    x += spCos;
    y += spSin;
}