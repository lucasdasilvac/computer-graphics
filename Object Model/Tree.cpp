#include "Tree.h"

Tree::Tree()
{

}

void Tree::draw()
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

                glBegin(GL_POLYGON);
                glNormal3f(0,0,0);

                if (this->selected) {
                    glColor3f(0, 0, 1);
                } else {
                    glColor3f(1, 0, 0);
                }

                for (int i =0; i < 360; i++) {
                    glVertex3f(0.2*cos(i), 2.5, 0.2*sin(i));
                    glVertex3f(0.2*cos(i), 0, 0.2*sin(i));
                }

                glEnd();
                if (this->selected) {
                    glColor3f(0, 0, 1);
                } else {
                    glColor3f(0, 1, 0);
                }

                glRotated(-90,1,0,0);
                glTranslated(0,0,1);
                glutWireCone(1, 2, 100, 10000);


            glPopMatrix();

        glPopMatrix();
    glPopMatrix();
}

void Tree::saveObject(std::fstream &file)
{
    file << "3" << " ";
    file << this->tx << " " << this->ty << " " << this->tz << " ";
    file << this->ax << " " << this->ay << " " << this->az << " ";
    file << this->sx << " " << this->sy << " " << this->sz << " ";
    file << this->selected << " ";
    file << this->axis;
}
