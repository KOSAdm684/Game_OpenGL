#ifndef TANK_H
#define TANK_H
#include "Tower.h"


class Tank
{
public:
    float x;
    float y;

    // Speed Direction
    float speed = 0;
    int moveDir = 0;

    // Speed limits
    float maxSpeedForward = 0;
    float maxSpeedBack = 0;

    float power;

    bool engineState = false;

    float angle;
    float rotateSpeed;

    float size;

    float *color;

    Tower *tower;

    Tank(float xPos, float yPos, float size, float *color, float angle, float rotSp, float pw, float maxFS, float maxBS);
    Tank();
    void Move();
    void Rotate(int dir);
};

#endif