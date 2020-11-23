#include "GunShell.h"
#include <math.h>

GunShell::GunShell(float xPos, float yPos, float size, float *color, float angle, float maxFS, float maxBS)
{
    x = xPos;
    y = yPos;
    this->size = size;
    maxSpeedForward = maxFS;
    maxSpeedBack = maxBS;
    this->color = color;
    this->angle = angle;
}

GunShell::GunShell()
{
    x = 0;
    y = 0;
    size = 0;
    angle = 0;
}

void GunShell::Move()
{
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
    float spC = speed * cos(angle);
    float spS = speed * sin(angle);
    x += spC;
    y += spS;
    moveDir = 0;
}

void GunShell::Rotate(int dir)
{
    const float dA = dir * 0.01 * (1.5 - fabs(speed) / maxSpeedForward);
    angle += dA;
    // tower->RotateWithTank(dA);
    speed *= 0.97;
}