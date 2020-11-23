#ifndef GUNSHELL_H
#define GUNSHELL_H

class GunShell
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

    float angle;

    float size;

    float *color;

    GunShell(float xPos, float yPos, float size, float *color, float angle, float maxFS, float maxBS);
    GunShell();
    void Move();
    void Rotate(int dir);
};

#endif