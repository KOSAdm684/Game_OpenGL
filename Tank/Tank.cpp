#include "Tank.h"
#include <math.h>

Tank::Tank(float xPos, float yPos, 
    float size, float *color, 
    float angle, float rotSp, 
    float pw, float maxFS, float maxBS, 
    float offX, float offY)
{
    x = xPos;
    y = yPos;
    this->size = size;
    maxSpeedForward = maxFS;
    maxSpeedBack = maxBS;
    this->color = color;
    this->angle = angle;
    tower = new Tower(xPos, yPos, angle, offX * size, offY * size);
    rotateSpeed = rotSp;
    power = pw;
    rTime = 300;
}

Tank::Tank() {}

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
    float spX = speed * cos(angle);
    float spY = speed * sin(angle);

    x += spX;
    y += spY;
    tower->x += spX;
    tower->y += spY;

    moveDir = 0;
    if (rTime > 0)
    { 
        rTime--;
    }
}

void Tank::Rotate(int dir)
{
    const float dA = dir * 0.01 * (1.5 - fabs(speed) / maxSpeedForward);
    angle += dA;
    tower->RotateWithTank(dA);
    speed *= 0.97;
}

GunShell* Tank::Shoot()
{
    GunShell* gunShell = NULL;
    if (rTime == 0)
    {
        const float tmpX = tower->bodyOffsetX * cosf(angle) - tower->bodyOffsetY * sinf(angle);
        const float tmpY = tower->bodyOffsetX * sinf(angle) + tower->bodyOffsetY * cosf(angle);

        const float tmpXG = x + tmpX + size * (0.8 * cosf(tower->angle));
        const float tmpYG = y + tmpY + size * (0.8 * sinf(tower->angle));
        
        gunShell = new GunShell(tmpXG, tmpYG, 15, new float[3] { 0.0, 0.0, 0.0 }, tower->angle);
        rTime = 300;
    }
    return gunShell;
}