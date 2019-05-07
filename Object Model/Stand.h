#ifndef STAND_H
#define STAND_H

#include "Object.h"

class Stand : public Object
{
public:
    Stand();

    void draw();
    void saveObject(std::fstream &file);
};

#endif // STAND_H
