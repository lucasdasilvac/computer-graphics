#include "Object.h"

Object::Object()
{

}

void Object::setSelected(bool selected)
{
    this->selected = selected;
}

void Object::setAxis(bool axis)
{
    this->axis = axis;
}

void Object::setShadow(bool shadow)
{
    this->shadow = shadow;
}

void Object::draw()
{

}

void Object::saveObject(std::fstream &file)
{

}
