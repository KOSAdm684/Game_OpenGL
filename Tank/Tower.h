#ifndef TOWER_H
#define TOWER_H
#include "../Object/Object.h"

class Tower : public Object
{
public:
    float bodyOffsetX;
    float bodyOffsetY;

    Tower(float X, float Y, float Angle, float offX, float offY);
    void RotateWithTank(float dA);
    void Move();
    void Rotate(int dir);
};

#endif