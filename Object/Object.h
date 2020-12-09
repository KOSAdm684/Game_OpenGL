#ifndef OBJECT_H
#define OBJECT_H

class Object
{
public:
    float x = 0;
    float y = 0;

    float size = 0;

    float angle = 0;

    float speed = 0;

    Object *previous = nullptr;
    Object *next = nullptr;

    virtual void Move() = 0;
};

#endif