#ifndef GROUND_H
#define GROUND_H

#include "Object.h"

class Ground : public Object
{
public:
    Ground();

    void draw();
    void saveObject(std::fstream &file);
};

#endif // GROUND_H
