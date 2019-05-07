#include <GL/glut.h>
#include <iostream>
#include <iomanip>
#include <vector>

#include "Object.h"
#include "Stand.h"
#include "Car.h"
#include "Tree.h"
#include "TennisCourt.h"
#include "Ball.h"
#include "Racket.h"
#include "Ground.h"

using namespace std;

#include "CameraDistante.h"
#include "Desenha.h"

#include "stanfordbunny.h"
#include "model3ds.h"

// Global Variables.

GLuint gBunnyWireList = NULL;
GLuint gBunnySolidList = NULL;

vector <Object*> objects;
int idxSelected = -1;
bool axis = false;

int width = 800;
int height = 600;

int slices = 16;
int stacks = 16;

float trans_obj = false;

float tx = 0.0;
float ty = 0.0;
float tz = 0.0;

float ax = 0.0;
float ay = 0.0;
float az = 0.0;

float delta = 5.0;

float sx = 1.0;
float sy = 1.0;
float sz = 1.0;

// Local Point.
float pl[4] = { 0.0, 0.0, 0.0, 1.0 };

// Global Point.
float pg[4] = { 0.0, 0.0, 0.0, 1.0 };

bool lbpressed = false;
bool mbpressed = false;
bool rbpressed = false;

float last_x = 0.0;
float last_y = 0.0;

// Cameras.
Camera* cam1 = new CameraDistante();
Camera* cam2 = new CameraDistante(-3,2,-5, 0,0,0, 0,1,0);

float savedCamera[9];

bool manual_cam = false;
bool change_manual_cam = false;

void mult_matrix_vector(float x[4], float matrix[16], float y[4]) {
    for (int i = 0; i < 4; i++) {
        x[i] = 0.0;
        for (int j = 0; j < 4; j++) {
            x[i] += matrix[4*j+i] * y[j];
        }
    }
}

void show_matrix_transform(float matrix[16], bool transposed = true) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (!transposed) {
                cout << setiosflags (ios::fixed) << setprecision(2) << matrix[4*i+j] << "  ";
            } else {
                cout << setiosflags (ios::fixed) << setprecision(2) << matrix[4*j+i] << "  "; // matrix ^ T
            }
        }
        cout << "\n";
    }
}

void show_coordinates_local_global()
{
    cout << "local coordinates: " << pl[0] << ", " << pl[1] << ", " << pl[2] << "\n";

        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
            glLoadIdentity();

              glTranslated(tx,ty,tz);
              glRotated(az,0,0,1);
              glRotated(ay,0,1,0);
              glRotated(ax,1,0,0);

            float change_coordinates_system[16];
            glGetFloatv(GL_MODELVIEW_MATRIX, change_coordinates_system);
            cout << " local -> global (T.Rz.Ry.Rx):\n ";
            show_matrix_transform(change_coordinates_system);
            mult_matrix_vector(pg, change_coordinates_system, pl);
            cout << "global coordinates: " << pg[0] << ", " << pg[1] << ", " << pg[2] << "\n\n";
        glPopMatrix();
}

void draw_cam(float size) {
    GLUquadricObj *quad = gluNewQuadric();

    glPushMatrix();
    glPopMatrix();

    gluDeleteQuadric( quad );
}

void transform_cam_2_global(Vetor3D e, Vetor3D c, Vetor3D u, bool show_matrix = false)
{
    // Matrix.
        float transform[16] = {
                                1.0,    0.0,    0.0,    0.0,
                                0.0,    1.0,    0.0,    0.0,
                                0.0,    0.0,    1.0,    0.0,
                                0.0,    0.0,    0.0,    1.0
                             };
        glMultTransposeMatrixf( transform );

    if (show_matrix) {
        cout << " cam2 -> global (R t = x' y' z' e):\n";
        show_matrix_transform(transform, false);
        cout << "\n";
    }
}

void transform_global_2_cam(Vetor3D e, Vetor3D c, Vetor3D u, bool show_matrix = false)
{
    // Matrix.
        float transform[16] = {
                                1.0,    0.0,    0.0,    0.0,
                                0.0,    1.0,    0.0,    0.0,
                                0.0,    0.0,    1.0,    0.0,
                                0.0,    0.0,    0.0,    1.0
                             };
        glMultTransposeMatrixf( transform );

    if (show_matrix) {
        cout << " global -> cam2 (R^T -R^T.t):\n";
        show_matrix_transform(transform, false);
        cout << "\n";
    }
}


/* GLUT callback Handlers */

void resize(int w, int h)
{
    width = w;
    height = h;
}

void displayInit()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    const float ar = height>0 ? (float) width / (float) height : 1.0;

    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(30.,ar,0.1,1000.);

}

void displayEnd()
{
    glutSwapBuffers();
}

void displayInner(bool manual_cam)
{
    const double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
        gluLookAt(cam1->e.x,cam1->e.y,cam1->e.z, cam1->c.x,cam1->c.y,cam1->c.z, cam1->u.x,cam1->u.y,cam1->u.z);

    // Global System.
    glPushMatrix();
        Desenha::drawEixos( 1.0 );

        glColor3d(0.3,0.3,0.3);

        Desenha::drawGrid( 10, 0, 10, 1 );
    glPopMatrix();

    // Local System.
    glPushMatrix();
    for (int i = 0; i < objects.size(); i++) {
        glPushMatrix();
            objects[i]->draw();
        glPopMatrix();
    }
    glPopMatrix();

    // System Local Camera.
        glPushMatrix();
            transform_cam_2_global(cam2->e,cam2->c,cam2->u);

            glColor3d(0.5,0.5,0.0);

            draw_cam(0.2);
        glPopMatrix();

}

void display()
{
    displayInit();
    displayInner(manual_cam);
    displayEnd();
}

void mouseButton(int button, int state, int x, int y) {
	// if the left button is pressed
	if (button == GLUT_LEFT_BUTTON) {
		// when the button is pressed
		if (state == GLUT_DOWN) {
            lbpressed = true;
		} else {// state = GLUT_UP
            lbpressed = false;
		}
	}
	// if the middle button is pressed
	if (button == GLUT_MIDDLE_BUTTON) {
		// when the button is pressed
		if (state == GLUT_DOWN) {
            mbpressed = true;
		} else {// state = GLUT_UP
            mbpressed = false;
		}
	}
	// if the left button is pressed
	if (button == GLUT_RIGHT_BUTTON) {
		// when the button is pressed
		if (state == GLUT_DOWN) {
            rbpressed = true;
		} else {// state = GLUT_UP
            rbpressed = false;
		}
	}

    last_x = x;
    last_y = y;
}

void mouseMove(int x, int y) {
    float factor = 10.0;
    if (lbpressed && !rbpressed && !mbpressed) {
        if (!trans_obj) {
            if (!manual_cam) {
                if (!change_manual_cam) {
                    cam1->rotatex(y,last_y);
                    cam1->rotatey(x,last_x);
                } else {
                    cam2->rotatex(last_y,y);
                    cam2->rotatey(last_x,x);
                }
            } else {
                if (!change_manual_cam) {
                    cam1->rotatex(last_y,y);
                    cam1->rotatey(last_x,x);
                } else {
                    cam2->rotatex(y,last_y);
                    cam2->rotatey(x,last_x);
                }
            }
        } else {
            objects[idxSelected]->ax += (y - last_y)/factor;
            objects[idxSelected]->ay += (x - last_x)/factor;
        }
    }
    factor = 100.0;
    if (!lbpressed && rbpressed && !mbpressed) {
        if (!trans_obj) {
            if (!manual_cam) {
                if (!change_manual_cam) {
                    cam1->translatex(x,last_x);
                    cam1->translatey(y,last_y);
                } else {
                    cam2->translatex(last_x,x);
                    cam2->translatey(last_y,y);
                }
            } else {
                if (!change_manual_cam) {
                    cam1->translatex(last_x,x);
                    cam1->translatey(last_y,y);
                } else {
                    cam2->translatex(x,last_x);
                    cam2->translatey(y,last_y);
                }
            }
        } else {
            objects[idxSelected]->tx += (x - last_x)/factor;
            objects[idxSelected]->ty += -(y - last_y)/factor;
        }
    }
    if (lbpressed && rbpressed && !mbpressed) {
        if (!trans_obj) {
            if (!manual_cam) {
                if (!change_manual_cam) {
                    cam1->zoom(y,last_y);
                } else {
                    cam2->zoom(last_y,y);
                }
            } else {
                if (!change_manual_cam) {
                    cam1->zoom(last_y,y);
                } else {
                    cam2->zoom(y,last_y);
                }
            }
        } else {
            objects[idxSelected]->tz += (y - last_y)/factor;
            factor = 10.0;
            objects[idxSelected]->az += -(x - last_x)/factor;
        }
    }
    factor = 100.0;
    if (!lbpressed && !rbpressed && mbpressed) {
        if (!trans_obj) {
        } else {
            objects[idxSelected]->sx += (x - last_x)/factor;
            objects[idxSelected]->sy += -(y - last_y)/factor;
        }
    }
    if (lbpressed && !rbpressed && mbpressed) {
        if (!trans_obj) {
        } else {
            objects[idxSelected]->sz += (y - last_y)/factor;
        }
    }
    if (!lbpressed && rbpressed && mbpressed) {
        if (!trans_obj) {
        } else {
            pl[0] += (x - last_x)/factor;
            pl[1] += -(y - last_y)/factor;
            show_coordinates_local_global();
        }
    }

    last_x = x;
    last_y = y;
}

void saveVectorObject() {
    fstream f;
    f.open("object-model.txt", fstream::out);

    for (Object* object : objects) {
        object->saveObject(f);
        f << endl;
    }
    f.close();
}

void loadObjects() {
    fstream f;
    f.open("object-model.txt", fstream::in);

    string object;

    Vetor3D pos, ang, sc;

    bool isSelected, isAxis;

    int i = 0;

    while (f >> object) {
        f >> pos.x >> pos.y >> pos.z;
        f >> ang.x >> ang.y >> ang.z;
        f >> sc.x >> sc.y >> sc.z;
        f >> isSelected;
        f >> isAxis;

        if (object == "1") {
            objects.push_back(new Stand());
        } else if (object == "2") {
            objects.push_back(new Car());
        } else if (object == "3") {
            objects.push_back(new Tree());
        } else if (object == "4") {
            objects.push_back(new TennisCourt());
        } else if (object == "5") {
            objects.push_back(new Ball());
        } else if (object == "6") {
            objects.push_back(new Racket());
        } else if (object == "7") {
            objects.push_back(new Ground());
        }

        // T
        objects[i]->tx = pos.x;
        objects[i]->ty = pos.y;
        objects[i]->tz = pos.z;

        // R
        objects[i]->ax = ang.x;
        objects[i]->ay = ang.y;
        objects[i]->az = ang.z;

        // S
        objects[i]->sx = sc.x;
        objects[i]->sy = sc.y;
        objects[i]->sz = sc.z;

        objects[i]->setSelected(isSelected);
        objects[i]->setAxis(isAxis);

        i++;
    }
    f.close();
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 'q':
            exit(0);
            break;

        case 'F':
            glutFullScreen();
            break;
        case 'f':
            glutReshapeWindow(800,600);
            break;

        case 'v':
            saveVectorObject();
            break;

        case 'l':
            objects.clear();
            loadObjects();
            break;

        case 'a':
            if (!objects.empty()) {
                if (idxSelected >= 0 && idxSelected < objects.size()) {
                    objects[idxSelected]->axis = !objects[idxSelected]->axis;
                }
            }
            break;

        case '>':
        if(idxSelected == -1) {
            if (objects.size() > 0) {
                idxSelected = 0;
                objects[idxSelected]->setSelected(true);
            }
        } else if (idxSelected == (objects.size() - 1)) {
            objects[idxSelected]->setSelected(false);
            idxSelected = -1;
        } else {
            objects[idxSelected]->setSelected(false);
            idxSelected++;
            objects[idxSelected]->setSelected(true);
        }

        break;

        case 'r':
            if (!objects.empty()) {
                vector<Object*> tmp;
                vector<Object*>::iterator it, _it;

                for (it = objects.begin(); it != objects.end(); it++) {
                    tmp.push_back(*it);
                }

                if (idxSelected >= 0 && idxSelected < objects.size()) {
                    for (it = objects.begin(); it != objects.end(); it++) {
                        if (*it == objects[idxSelected]) {
                            objects.erase(objects.begin(), objects.end());
                            for (_it = tmp.begin(); _it != tmp.end(); _it++) {
                                if (*it != *_it) {
                                    objects.push_back(*_it);
                                }
                            }
                            if (idxSelected == (objects.size() - 1)) {
                                idxSelected = -1;
                            } else if (idxSelected == 0) {
                                idxSelected--;
                            } else {
                                idxSelected--;
                                objects[idxSelected]->setSelected(true);
                            }
                            break;
                        }
                    }
                }
            }
            break;

        case '1': {
            Stand * stand = new Stand();
            objects.push_back(stand);
            stand = nullptr;
            break;
        }

        case '2': {
            Car * car = new Car();
            objects.push_back(car);
            car = nullptr;
            break;
        }

        case '3': {
            Tree * tree = new Tree();
            objects.push_back(tree);
            tree = nullptr;
            break;
        }

        case '4': {
            TennisCourt * tennisCourt = new TennisCourt();
            objects.push_back(tennisCourt);
            tennisCourt = nullptr;
            break;
        }

        case '5': {
            Ball * ball = new Ball();
            objects.push_back(ball);
            ball = nullptr;
            break;
        }

        case '6': {
            Racket * racket = new Racket();
            objects.push_back(racket);
            racket = nullptr;
            break;
        }

        case '7': {
            Ground * ground = new Ground();
            objects.push_back(ground);
            ground = nullptr;
            break;
        }

        case '+':
            slices++;
            stacks++;
            break;

        case '-':
            if (slices>3 && stacks>3)
            {
                slices--;
                stacks--;
            }
            break;

        case 'X':
            // ax+=delta;
            if(trans_obj) ax+=delta;
            else { pl[0] += 0.01; show_coordinates_local_global(); };
            break;

        case 'Y':
            // ay+=delta;
            if(trans_obj) ay+=delta;
            else { pl[1] += 0.01; show_coordinates_local_global(); };
            break;

        case 'Z':
            // az+=delta;
            if(trans_obj) az+=delta;
            else { pl[2] += 0.01; show_coordinates_local_global(); };
            break;

        case 'x':
            // ax-=delta;
            if(trans_obj) ax-=delta;
            else { pl[0] -= 0.01; show_coordinates_local_global(); };
            break;

        case 'y':
            // ay-=delta;
            if(trans_obj) ay-=delta;
            else { pl[1] -= 0.01; show_coordinates_local_global(); };
            break;

        case 'z':
            // az-=delta;
            if(trans_obj) az-=delta;
            else { pl[2] -= 0.01; show_coordinates_local_global(); };
            break;

        case 'i':
            ax=ay=az=0.0;
            tx=ty=tz=0.0;
            sx=sy=sz=1.0;
            break;

        case 't':
            trans_obj = !trans_obj;
            break;

        case 'c':
            static int idxCam1 = 0;
            idxCam1++;
            if (cam1->estilo == 1) {
                delete cam1;
                if (idxCam1%5==0) cam1 = new CameraDistante();
                // up
                if (idxCam1%5==1) cam1 = new CameraDistante(0.0671324,10.9985,0.161224, 0,1,0, -0.384342,0.0174642,-0.923026);
                // farther
                if (idxCam1%5==2) cam1 = new CameraDistante(-0.279056, 27.9024, 43.9763, -0.138833, -1.31933, 0, 0.00176469, 0.832888, -0.553439);
                // back diagonal
                if (idxCam1%5==3) cam1 = new CameraDistante(-27.7386, 14.4946, -27.16, -0.348222, 1.14659, 0.0488028, 0.231819, 0.945108, 0.230282);

                if (idxCam1%5==4) cam1 = new CameraDistante(savedCamera[0],savedCamera[1],savedCamera[2],savedCamera[3],savedCamera[4],savedCamera[5],savedCamera[6],savedCamera[7],savedCamera[8]);
            } else if (cam1->estilo == 2) {
                delete cam1;
                cam1 = new CameraDistante();
            }
            break;

        case 'C':
            static int idx_manual_cam = 0;
            idx_manual_cam++;
            if (idx_manual_cam%4==0) {
                cout << "showing cam1, changing cam1: \n";
                change_manual_cam = false;
                manual_cam = false;
            }
            if (idx_manual_cam%4==1) {
                cout << "showing cam1, changing cam2: \n";
                change_manual_cam = true;
                manual_cam = false;
            }
            if (idx_manual_cam%4==2) {
                cout << "showing cam2, changing cam2: \n";
                change_manual_cam = true;
                manual_cam = true;
            }
            if (idx_manual_cam%4==3) {
                cout << "showing cam2, changing cam1: \n";
                change_manual_cam = false;
                manual_cam = true;
            }
            if (manual_cam) {
                glPushMatrix();
                    transform_global_2_cam(cam2->e,cam2->c,cam2->u,true);
                glPopMatrix();
            } else {
                glPushMatrix();
                    transform_cam_2_global(cam2->e,cam2->c,cam2->u,true);
                glPopMatrix();
            }
            break;

        case 's':
            // save current camera location
            savedCamera[0] = cam1->e.x;
            savedCamera[1] = cam1->e.y;
            savedCamera[2] = cam1->e.z;
            savedCamera[3] = cam1->c.x;
            savedCamera[4] = cam1->c.y;
            savedCamera[5] = cam1->c.z;
            savedCamera[6] = cam1->u.x;
            savedCamera[7] = cam1->u.y;
            savedCamera[8] = cam1->u.z;

            for (int i = 0; i < 9; i++) {
                cout << savedCamera[i] << ", ";
            }

            break;

        case 'm':
            if (!manual_cam) {
                glMatrixMode(GL_MODELVIEW);
                glPushMatrix();
                    glLoadIdentity();
                      glTranslated(tx,ty,tz);
                      glRotated(az,0,0,1);
                      glRotated(ay,0,1,0);
                      glRotated(ax,1,0,0);
                      glScaled(sx,sy,sz);
                    float transform[16];
                    glGetFloatv(GL_MODELVIEW_MATRIX,transform);
                    cout << "(T.Rz.Ry.Rx.S):\n";
                    show_matrix_transform(transform);
                    cout << "\n";
                glPopMatrix();
            } else {
                glMatrixMode(GL_MODELVIEW);
                glPushMatrix();
                    glLoadIdentity();
                      gluLookAt(cam2->e.x,cam2->e.y,cam2->e.z, cam2->c.x,cam2->c.y,cam2->c.z, cam2->u.x,cam2->u.y,cam2->u.z);
                    float transform[16];
                    glGetFloatv(GL_MODELVIEW_MATRIX,transform);
                    cout << "Matrix gluLookAt:\n";
                    show_matrix_transform(transform);
                    cout << "\n";
                glPopMatrix();
            }
            break;
    }

    glutPostRedisplay();
}

void idle(void)
{
    glutPostRedisplay();
}

/* Program entry point */

int main(int argc, char *argv[])
{
        glutInit(&argc, argv);
        glutInitWindowSize(width,height);
        glutInitWindowPosition(10,10);
        glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

        glutCreateWindow("Object Model");

        glutReshapeFunc(resize);
        glutDisplayFunc(display);
        glutKeyboardFunc(keyboard);
        glutIdleFunc(idle);

        glutMouseFunc(mouseButton);
        glutMotionFunc(mouseMove);

    // OpenGL.
        glClearColor(1,1,1,1);

        glEnable(GL_LIGHTING);
        glEnable(GL_COLOR_MATERIAL);
        // glEnable(GL_CULL_FACE);
        // glCullFace(GL_BACK);
        glEnable(GL_NORMALIZE);

        glShadeModel(GL_SMOOTH);

        glEnable(GL_DEPTH_TEST);
        // glDepthFunc(GL_LESS);

        // glEnable(GL_BLEND);
        // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        // Light.
            glEnable(GL_LIGHT0);

            const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
            const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
            const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
            const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

            const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
            const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
            const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
            const GLfloat high_shininess[] = { 100.0f };

            glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
            glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
            glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
            glLightfv(GL_LIGHT0, GL_POSITION, light_position);

            glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
            glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
            glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
            glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);

        glutMainLoop();

    return EXIT_SUCCESS;
}
