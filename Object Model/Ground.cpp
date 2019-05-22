#include "Ground.h"

Ground::Ground()
{

}

void Ground::draw()
{
    glPushMatrix();
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

                glBegin(GL_QUADS);
                glNormal3f(0,0,0);

                if(this->shadow) {
                    glColor3f(0, 0, 0);
                } else {
                    if (this->selected) {
                        glColor3f(0, 0, 1);
                    } else {
                        glColor3f(0, 1, 0);
                    }
                }

                glVertex3f(-5, 0,  5);
                glVertex3f(-5, 0, -5);
                glVertex3f( 5, 0, -5);
                glVertex3f( 5, 0,  5);

                glEnd();


            glPopMatrix();

        glPopMatrix();
    glPopMatrix();
}

void Ground::saveObject(std::fstream &file)
{
    file << "7" << " ";
    file << this->tx << " " << this->ty << " " << this->tz << " ";
    file << this->ax << " " << this->ay << " " << this->az << " ";
    file << this->sx << " " << this->sy << " " << this->sz << " ";
    file << this->selected << " ";
    file << this->axis;
}
