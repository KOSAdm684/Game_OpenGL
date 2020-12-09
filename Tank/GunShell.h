#ifndef GUNSHELL_H
#define GUNSHELL_H
#include "../Object/Object.h"

class GunShell : public Object
{
public:
    float *color;

    GunShell(float xPos, float yPos, float size, float *color, float angle);
    GunShell();
    void Move();
};

#endif