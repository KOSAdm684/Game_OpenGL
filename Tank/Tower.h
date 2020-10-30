#ifndef TOWER_H
#define TOWER_H

class Tower
{
public:
    float x;
    float y;

    float angle;

    Tower(float X, float Y, float Angle);
    void RotateWithTank(float rot);
    void Move(float spCos, float spSin);
};

#endif