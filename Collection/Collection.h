#ifndef COLLECTION_H
#define COLLECTION_H

#include "../Object/Object.h"

class Collection
{
public:
    Object *first;
    Object *last;

    unsigned count;

    Collection();

    void Delete(Object *obj);
    void Add(Object *obj);
};

#endif