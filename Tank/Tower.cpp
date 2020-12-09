#include "Tower.h"

Tower::Tower(float X, float Y, float Angle, float offX, float offY)
{
    x = X;
    y = Y;
    angle = Angle;
    bodyOffsetX = offX;
    bodyOffsetY = offY;
}

void Tower::RotateWithTank(float dA)
{
    angle += dA;
}

void Tower::Rotate(int dir)
{
    const float dA = dir * 0.0125;
    angle += dA;
}

void Tower::Move() {}