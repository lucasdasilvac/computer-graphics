#ifndef TREE_H
#define TREE_H

#include "Object.h"

class Tree : public Object
{
public:
    Tree();

    void draw();
    void saveObject(std::fstream &file);
};

#endif // TREE_H
