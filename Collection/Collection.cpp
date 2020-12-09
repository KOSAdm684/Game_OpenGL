#include "Collection.h"

Collection::Collection()
{
    count = 0;
    first = nullptr;
    last = nullptr;
}

void Collection::Add(Object *obj)
{
    if (count == 0)
    {
        first = obj;
        last = obj;
    }
    else
    {
        last->next = obj;
        last = obj;
    }

    count++;
}

void Collection::Delete(Object *obj)
{
    Object *next = obj->next;
    Object *previous = obj->previous;

    if (previous)
    {
        previous->next = next;
    }
    else
    {
        first = next;
    }

    if (next)
    {
        next->previous = previous;
    }
    else
    {
        last = previous;
    }

    delete(obj);

    count--;
}