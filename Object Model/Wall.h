#ifndef WALL_H
#define WALL_H

#include "Object.h"

class Wall : public Object
{
public:
    Wall();

    void draw();
    void saveObject(std::fstream &file);
};

#endif // WALL_H
