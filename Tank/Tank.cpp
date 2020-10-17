#include "Tank.h"
#include <math.h>

Tank::Tank(float xPos, float yPos, float size, float *color, float angle, float rotSp, float pw)
{
    x = xPos;
    y = yPos;
    this->size = size;
    speedX = 0;
    speedY = 0;
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
    speedX = 0;
    speedY = 0;
    angle = 0;
}

void Tank::Move()
{
    float dspX = -0.02f * cos(angle); // Базовое трение
    float dspY = -0.02f * sin(angle);

    if (engineState)
    {
        dspX += power * cos(angle);
        dspY += power * sin(angle);
        speedX += dspX * speed;
        speedY += dspY * speed;
    }
    else
    {
        float friction = powf(powf(dspX, 2.0f) + powf(dspY, 2.0f), 0.5f);
        float speedV = powf(powf(speedX, 2.0f) + powf(speedY, 2.0f), 0.5f);
        if (friction > speedV)
        {
            speedX = 0;
            speedY = 0;
        }
        else
        {
            speedX += dspX * speed;
            speedY += dspY * speed;
        }
        
    }
    
    x += speedX;
    y += speedY;
}

void Tank::Rotate(int dir)
{
    const float dA = rotateSpeed * dir;
    angle += dA;
    float spX = speedX * cos(dA) - speedY * sin(dA);
    float spY = speedX * sin(dA) + speedY * cos(dA);
    speedX = spX * 0.99f;
    speedY = spY * 0.99f;
}