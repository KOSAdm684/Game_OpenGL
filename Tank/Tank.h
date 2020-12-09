#ifndef TANK_H
#define TANK_H
#include "Tower.h"
#include "GunShell.h"
#include "../Object/Object.h"


class Tank : public Object
{
public:
    // Speed Direction
    int moveDir = 0;

    // Speed limits
    float maxSpeedForward = 0;
    float maxSpeedBack = 0;

    float power;

    bool engineState = false;

    float rotateSpeed;

    float size;

    float *color;

    Tower *tower;

    GunShell *gunShell;

    unsigned rTime;

    Tank(float xPos, float yPos, float size, float *color, float angle, float rotSp, float pw, float maxFS, float maxBS, float offX, float offY);
    Tank();
    GunShell* Shoot();
    void Move();
    void Rotate(int dir);
};

#endif