#include <GL/freeglut.h>

#include "global.h"
#include "octahedron.h"

using namespace std;
using namespace GL_WR;

void GL_WR::octahTimer(int iUnused)
{
    //Logic
    glutPostRedisplay();
    glutTimerFunc(30, octahTimer, 0);
}

void GL_WR::octahRender(void) {
    glClear(GL_COLOR_BUFFER_BIT);

    glPushAttrib(GL_LINE_BIT);

    glClear(GL_COLOR_BUFFER_BIT);
    color3f(GL_WR::green);
    glBegin(GL_POLYGON);
        glVertex3f(0.5, 0.0, 0.5);
        glVertex3f(0.5, 0.0, 0.0);
        glVertex3f(0.0, 0.5, 0.0);
        glVertex3f(0.0, 0.0, 1.0);
    glEnd();
    glFlush();


    glPopAttrib();
    glFlush();
}

void GL_WR::octahReshape(int Width, int Height)
{
    octahRender();
}

void GL_WR::octahKeyboard(int key, int x, int y)
{
    switch(key)
    {
        case GLUT_KEY_F1:
            std::cout << "F1 is pressed\n";
            break;
    }
    glutPostRedisplay();
}
