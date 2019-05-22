#include "TennisCourt.h"

TennisCourt::TennisCourt()
{
    model = new Model3DS("3DS/tennis_court.3DS");
}

void TennisCourt::draw()
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

            if(this->shadow) {
                glColor3f(0, 0, 0);
            } else {
                if (this->selected) {
                    glColor3f(0, 0, 1);
                } else {
                    // amarelo esverdeado
                    glColor3f(0.68, 1, 0.18);
                }
            }
            glRotated(-90, 1, 0, 0);
            glScaled(0.25, 0.25, 0.25);
            model->draw();

        glPopMatrix();
    glPopMatrix();

}

void TennisCourt::saveObject(std::fstream &file)
{
    file << "4" << " ";
    file << this->tx << " " << this->ty << " " << this->tz << " ";
    file << this->ax << " " << this->ay << " " << this->az << " ";
    file << this->sx << " " << this->sy << " " << this->sz << " ";
    file << this->selected << " ";
    file << this->axis;
}
