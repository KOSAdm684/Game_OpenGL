#include "Tank.h"
#include <math.h>

Tank::Tank(float xPos, float yPos, float size, float *color, float angle, float rotSp, float pw, float maxFS, float maxBS)
{
    x = xPos;
    y = yPos;
    this->size = size;
    maxSpeedForward = maxFS;
    maxSpeedBack = maxBS;
    this->color = color;
    this->angle = angle;
    rotateSpeed = rotSp;
    power = pw;
}

Tank::Tank()
{
    x = 0;
    y = 0;
    size = 0;
    angle = 0;
}

void Tank::Move()
{
    speed += moveDir * power;

    const float friction = (speed > 0 ? 1 : -1) * 0.08;

    if (abs(friction) > abs(speed))
    {
        speed = 0;
    }
    else
    {
        speed -= friction;

        if (speed > maxSpeedForward)
        {
            speed = maxSpeedForward;
        }
        if (speed < maxSpeedBack)
        {
            speed = maxSpeedBack;
        }
    }
    
    x += speed * cos(angle);
    y += speed * sin(angle);
    moveDir = 0;
}

void Tank::Rotate(int dir)
{
    const float dA = dir * 0.01 * (1.5 - abs(speed) / maxSpeedForward);
    angle += dA;
    speed *= 0.97;
}