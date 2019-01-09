#include <GL/freeglut.h>

#include "global.h"
#include "scene.h"
#include "octahedron.h"

using namespace std;
using namespace GL_WR;

extern Octahedron octah1;

Octahedron::Octahedron(GLfloat parametres)
{
    this->height        = parametres;
    this->base_width    = parametres;
    this->base_length   = parametres;
}

Octahedron::Octahedron(GLfloat base_parametres, GLfloat height)
{
    this->height        = height;
    this->base_width    = base_parametres;
    this->base_length   = base_parametres;
}

Octahedron::Octahedron(GLfloat base_width, GLfloat base_length, GLfloat height)
{
    this->height        = height;
    this->base_width    = base_width;
    this->base_length   = base_length;
}

Octahedron::Octahedron(const GLfloat2& a)
{
    Octahedron(a.x, a.y);
}

Octahedron::Octahedron(const GLfloat3& a)
{
    Octahedron(a.x, a.y, a.z);
}

void GL_WR::octahTimer(int iUnused)
{
    //Logic
    glutPostRedisplay();
    glutTimerFunc(GL_WR::Scene::getFIMS(), octahTimer, 0);
}

void GL_WR::octahRender(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Очистка экрана и буфера глубины

    glPushAttrib(GL_LINE_BIT);

    glLoadIdentity();   // Сброс просмотра
    glTranslatef(-octah1.base_length/2, -octah1.height/2, 0.0f); // Сдвиг влево экрана
    //
    // glRotatef(rtri, 0.0, 1.0, 0.0);
    // rtri = (rtri > 360) ? 0 : rtri+0.5;

    glClear(GL_COLOR_BUFFER_BIT);
    color3f(GL_WR::green);
    glBegin(GL_POLYGON);
        glVertex3f(octah1.base_length, 0.0, 0.0);
        glVertex3f(octah1.base_length/2, octah1.height, 0.0);
        glVertex3f(0.0, 0.0, 0.0);
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
