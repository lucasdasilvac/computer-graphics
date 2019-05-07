#ifndef CAR_H
#define CAR_H

#include "Object.h"
#include "model3ds.h"

class Car : public Object
{
    Model3DS * model;
public:
    Car();

    void draw();
    void saveObject(std::fstream &file);
};

#endif // CAR_H
