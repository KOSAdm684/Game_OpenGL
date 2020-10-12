#include "Tank.h"

Tank::Tank(float xPos, float yPos, float size, float *color)
{
    x = xPos;
    y = yPos;
    this->size = size;
    speedX = 0;
    speedY = 0;
    this->color = color;
}

Tank::Tank()
{
    x = 0;
    y = 0;
    size = 0;
    speedX = 0;
    speedY = 0;
}

void Tank::Move()
{
    x += speedX;
    y += speedY;
}