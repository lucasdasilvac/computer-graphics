#ifndef BALL_H
#define BALL_H

#include "Object.h"

class Ball : public Object
{
public:
    Ball();

    void draw();
    void saveObject(std::fstream &file);
};

#endif // BALL_H
