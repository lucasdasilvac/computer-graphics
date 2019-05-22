#include "Wall.h"

Wall::Wall()
{

}

void Wall::draw()
{
    glPushMatrix();
        glTranslated(this->tx,this->ty,this->tz);
        glRotated(this->az,0,0,1);
        glRotated(this->ay,0,1,0);
        glRotated(this->ax,1,0,0);
        glScaled(this->sx, this->sy, this->sz);

        glPushMatrix();

            if(this->axis){
                Desenha::drawEixos(0.5);
            }

        glPopMatrix();

        if(this->shadow) {
            glColor3f(0, 0, 0);
        } else {
            if (this->selected) {
                glColor3f(0, 0, 1);
            } else {
                glColor3f(1, 1, 1);
            }
        }

        glPushMatrix();
            glTranslatef(0.0,0.01,0.0);
            glPushMatrix();
                glBegin(GL_QUADS);
                    glVertex3f(-2.5,0.0,-0.2);
                    glVertex3f(2.5,0.0,-0.2);
                    glVertex3f(2.5,0.0,0.2);
                    glVertex3f(-2.5,0.0,0.2);
                glEnd();
            glPopMatrix();
            glPushMatrix();
                glBegin(GL_QUADS);
                    glVertex3f(-2.5,0.0,0.2);
                    glVertex3f(2.5,0.0,0.2);
                    glVertex3f(2.5,1.5,0.2);
                    glVertex3f(-2.5,1.5,0.2);
                glEnd();
            glPopMatrix();
            glPushMatrix();
                glBegin(GL_QUADS);
                    glVertex3f(-2.5,0.0,-0.2);
                    glVertex3f(2.5,0.0,-0.2);
                    glVertex3f(2.5,1.5,-0.2);
                    glVertex3f(-2.5,1.5,-0.2);
                glEnd();
            glPopMatrix();
            glPushMatrix();
                glBegin(GL_QUADS);
                    glVertex3f(-2.5,0.0,-0.2);
                    glVertex3f(-2.5,0.0,0.2);
                    glVertex3f(-2.5,1.5,0.2);
                    glVertex3f(-2.5,1.5,-0.2);
                glEnd();
            glPopMatrix();
            glPushMatrix();
                glBegin(GL_QUADS);
                    glVertex3f(2.5,0.0,-0.2);
                    glVertex3f(2.5,0.0,0.2);
                    glVertex3f(2.5,1.5,0.2);
                    glVertex3f(2.5,1.5,-0.2);
                glEnd();
            glPopMatrix();
            glPushMatrix();
                glBegin(GL_QUADS);
                    glVertex3f(-2.5,1.5,-0.2);
                    glVertex3f(2.5,1.5,-0.2);
                    glVertex3f(2.5,1.5,0.2);
                    glVertex3f(-2.5,1.5,0.2);
                glEnd();
            glPopMatrix();
        glPopMatrix();

        glPopMatrix();
}

void Wall::saveObject(std::fstream &file)
{
    file << "8" << " ";
    file << this->tx << " " << this->ty << " " << this->tz << " ";
    file << this->ax << " " << this->ay << " " << this->az << " ";
    file << this->sx << " " << this->sy << " " << this->sz << " ";
    file << this->selected << " ";
    file << this->axis;
}
