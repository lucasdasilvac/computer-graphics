#include "Car.h"

Car::Car()
{
    model = new Model3DS("3DS/car.3ds");
}

void Car::draw()
{
    glPushMatrix();
        glTranslated(this->tx,this->ty,this->tz);
        glRotated(this->az,0,0,1);
        glRotated(this->ay,0,1,0);
        glRotated(this->ax,1,0,0);
        glScaled(this->sx, this->sy, this->sz);

        glPushMatrix();
            if (this->axis) {
                Desenha::drawEixos( 0.5 );
            }
        glPopMatrix();

        glPushMatrix();
            glNormal3f(0,0,0);

            if (this->selected) {
                glColor3f(0, 0, 1);
            } else {
                // jambo
                glColor3f(1, 0.27, 0);
            }
            glRotated(-90, 1, 0, 0);
            model->draw();

        glPopMatrix();
    glPopMatrix();


}

void Car::saveObject(std::fstream &file)
{
    file << "2" << " ";
    file << this->tx << " " << this->ty << " " << this->tz << " ";
    file << this->ax << " " << this->ay << " " << this->az << " ";
    file << this->sx << " " << this->sy << " " << this->sz << " ";
    file << this->selected << " ";
    file << this->axis;
}
