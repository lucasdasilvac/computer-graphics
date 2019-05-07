#ifndef OBJECT_H
#define OBJECT_H

#include <math.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "GL/glut.h"
#include <fstream>
#include "Desenha.h"

class Object
{
public:
    Object();

    float tx = 0.0;
    float ty = 0.0;
    float tz = 0.0;

    float ax = 0.0;
    float ay = 0.0;
    float az = 0.0;

    float sx = 1.0;
    float sy = 1.0;
    float sz = 1.0;

    bool selected = false;
    bool axis = false;

    void setSelected(bool selected);
    void setAxis(bool axis);
    virtual void draw();
    virtual void saveObject(std::fstream &file) = 0;

};

#endif // OBJECT_H
