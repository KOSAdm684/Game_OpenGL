#include "GunShell.h"
#include <math.h>

GunShell::GunShell(float xPos, float yPos, float size, float *color, float angle)
{
    x = xPos;
    y = yPos;
    this->size = size;
    this->color = color;
    this->angle = angle;
    speed = 20;
}

GunShell::GunShell() {}

void GunShell::Move()
{
    x += speed * cos(angle);
    y += speed * sin(angle);
}