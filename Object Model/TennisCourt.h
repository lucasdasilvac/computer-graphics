#ifndef TENNISCOURT_H
#define TENNISCOURT_H

#include "Object.h"
#include "model3ds.h"

class TennisCourt : public Object
{
    Model3DS * model;
public:
    TennisCourt();

    void draw();
    void saveObject(std::fstream &file);
};

#endif // TENNISCOURT_H
