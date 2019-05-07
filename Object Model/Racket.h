#ifndef RACKET_H
#define RACKET_H

#include "Object.h"
#include "model3ds.h"

class Racket : public Object
{
    Model3DS * model;
public:
    Racket();

    void draw();
    void saveObject(std::fstream &file);
};

#endif // RACKET_H
