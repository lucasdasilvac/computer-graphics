#include "Stand.h"

Stand::Stand()
{

}

void Stand::draw()
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

            glTranslatef(0.0,0.01,0.0);

            // left side

            glPushMatrix();

                if (this->selected) {
                    glColor3f(0, 0, 1);
                } else {
                    // cobre
                    glColor3f(0.72, 0.45, 0.2);
                }

                glTranslatef(-5.0,0.0,0.0);
                glRotatef(90,0,1,0);
                glPushMatrix();
                    glBegin(GL_QUADS);
                        glVertex3f(-1.0,0.0,0.0);
                        glVertex3f(-3.0,0.0,0.0);
                        glVertex3f(-3.0,1.0,0.0);
                        glVertex3f(-1.0,1.0,0.0);
                    glEnd();
                glPopMatrix();
                glPushMatrix();
                    glBegin(GL_QUADS);
                        glVertex3f(-1.0,0.0,0.0);
                        glVertex3f(-1.0,2.0,0.0);
                        glVertex3f(1.0,2.0,0.0);
                        glVertex3f(1.0,0.0,0.0);
                    glEnd();
                glPopMatrix();
                glPushMatrix();
                    glBegin(GL_QUADS);
                        glVertex3f(1.0,0.0,0.0);
                        glVertex3f(1.0,3.0,0.0);
                        glVertex3f(3.0,3.0,0.0);
                        glVertex3f(3.0,0.0,0.0);
                    glEnd();
                glPopMatrix();
            glPopMatrix();

            // right side
            glPushMatrix();

                if (this->selected) {
                    glColor3f(0, 0, 1);
                } else {
                    // cobre
                    glColor3f(0.72, 0.45, 0.2);
                }

                glTranslatef(5.0,0.0,0.0);
                glRotatef(90,0,1,0);
                glPushMatrix();
                    glBegin(GL_QUADS);
                        glVertex3f(-1.0,0.0,0.0);
                        glVertex3f(-3.0,0.0,0.0);
                        glVertex3f(-3.0,1.0,0.0);
                        glVertex3f(-1.0,1.0,0.0);
                    glEnd();
                glPopMatrix();
                glPushMatrix();
                    glBegin(GL_QUADS);
                        glVertex3f(-1.0,0.0,0.0);
                        glVertex3f(-1.0,2.0,0.0);
                        glVertex3f(1.0,2.0,0.0);
                        glVertex3f(1.0,0.0,0.0);
                    glEnd();
                glPopMatrix();
                glPushMatrix();
                    glBegin(GL_QUADS);
                        glVertex3f(1.0,0.0,0.0);
                        glVertex3f(1.0,3.0,0.0);
                        glVertex3f(3.0,3.0,0.0);
                        glVertex3f(3.0,0.0,0.0);
                    glEnd();
                glPopMatrix();
            glPopMatrix();

            // back
            glPushMatrix();
                if (this->selected) {
                    glColor3f(0, 0, 1);
                } else {
                    // marrom claro
                    glColor3f(0.65, 0.16, 0.16);
                }
                    glBegin(GL_QUADS);
                        glVertex3f(5.0,0.0,-3.0);
                        glVertex3f(5.0,3.0,-3.0);
                        glVertex3f(-5.0,3.0,-3.0);
                        glVertex3f(-5.0,0.0,-3.0);
                    glEnd();
            glPopMatrix();

            glPushMatrix();
                    glBegin(GL_QUADS);
                        glVertex3f(5.0,0.0,3.0);
                        glVertex3f(5.0,1.0,3.0);
                        glVertex3f(-5.0,1.0,3.0);
                        glVertex3f(-5.0,0.0,3.0);
                    glEnd();
            glPopMatrix();

            glPushMatrix();
                    glBegin(GL_QUADS);
                        glVertex3f(5.0,1.0,1.0);
                        glVertex3f(5.0,2.0,1.0);
                        glVertex3f(-5.0,2.0,1.0);
                        glVertex3f(-5.0,1.0,1.0);
                    glEnd();
            glPopMatrix();

            glPushMatrix();
                    glBegin(GL_QUADS);
                        glVertex3f(5.0,2.0,-1.0);
                        glVertex3f(5.0,3.0,-1.0);
                        glVertex3f(-5.0,3.0,-1.0);
                        glVertex3f(-5.0,2.0,-1.0);
                    glEnd();
            glPopMatrix();

            glPushMatrix();
                    glBegin(GL_QUADS);
                        glVertex3f(5.0,1.0,3.0);
                        glVertex3f(5.0,1.0,1.0);
                        glVertex3f(-5.0,1.0,1.0);
                        glVertex3f(-5.0,1.0,3.0);
                    glEnd();
            glPopMatrix();

            glPushMatrix();
                    glBegin(GL_QUADS);
                        glVertex3f(5.0,2.0,1.0);
                        glVertex3f(5.0,2.0,-1.0);
                        glVertex3f(-5.0,2.0,-1.0);
                        glVertex3f(-5.0,2.0,1.0);
                    glEnd();
            glPopMatrix();

            glPushMatrix();
                    glBegin(GL_QUADS);
                        glVertex3f(5.0,3.0,-1.0);
                        glVertex3f(5.0,3.0,-3.0);
                        glVertex3f(-5.0,3.0,-3.0);
                        glVertex3f(-5.0,3.0,-1.0);
                    glEnd();
            glPopMatrix();

        glPopMatrix();
    glPopMatrix();
}

void Stand::saveObject(std::fstream &file)
{
    file << "1" << " ";
    file << this->tx << " " << this->ty << " " << this->tz << " ";
    file << this->ax << " " << this->ay << " " << this->az << " ";
    file << this->sx << " " << this->sy << " " << this->sz << " ";
    file << this->selected << " ";
    file << this->axis;
}
