#include <GL/freeglut.h>

#include "global.h"
#include "scene.h"
#include "octahedron.h"

using namespace std;
using namespace GL_WR;

extern Octahedron octah1;

Octahedron::Octahedron(GLfloat base_width, GLfloat base_length, GLfloat height)
{
    //Parametres
    this->height        = height;
    this->base_width    = base_width;
    this->base_length   = base_length;

    //Agels
    this->rotateY = 0;

    //Default speed of Agels
    this->stdSpeedRot = 0.8f;

    //Speed of Agels
    this->speedRot = stdSpeedRot;

    //Status
    this->isFrozen = false;
}

Octahedron::Octahedron(GLfloat base_parametres, GLfloat height)
{
    Octahedron(base_parametres, base_parametres, height);
}

Octahedron::Octahedron(GLfloat parametres)
{
    Octahedron(parametres, parametres);
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
    octah1.rotateY += octah1.speedRot;  // Увеличим переменную вращения

    glutPostRedisplay();
    glutTimerFunc(GL_WR::Scene::getFIMS(), octahTimer, 0);
}

void GL_WR::octahRender(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Очистка экрана и буфера глубины

    glPushAttrib(GL_LINE_BIT);

    glLoadIdentity();   // Сброс просмотра
    // glTranslatef(-octah1.base_length/2, -octah1.height/2, 0.0f); // Сдвиг влево экрана


    glClear(GL_COLOR_BUFFER_BIT);
    color3f(GL_WR::green);

    glRotatef(octah1.rotateY,1.0f,0.0f,0.0f);   // Вращение треугольника по оси Y

    glBegin(GL_TRIANGLES);  // Начало рисования треугольника
        // передняя грань
        glColor3f(1.0f,0.0f,0.0f);      // Красный
        glVertex3f( 0.0f, 0.5f, 0.0f);  // Верх треугольника (Передняя)
        glColor3f(0.0f,0.5f,0.0f);      // Зеленный
        glVertex3f(-0.5f,-0.5f, 0.5f);  // Левая точка
        glColor3f(0.0f,0.0f,1.0f);      // Синий
        glVertex3f( 0.5f,-0.5f, 0.5f);  // Правая точка

        // правая грань
        glColor3f(1.0f,0.0f,0.0f);      // Красная
        glVertex3f( 0.0f, 0.5f, 0.0f);  // Верх треугольника (Правая)
        glColor3f(0.0f,0.0f,1.0f);      // Синия
        glVertex3f( 0.5f,-0.5f, 0.5f);  // Лево треугольника (Правая)
        glColor3f(0.0f,1.0f,0.0f);      // Зеленная
        glVertex3f( 0.5f,-0.5f, -0.5f);  // Право треугольника (Правая)

        // задняя грань
        glColor3f(1.0f,0.0f,0.0f);      // Красный
        glVertex3f( 0.0f, 0.5f, 0.0f);  // Низ треугольника (Сзади)
        glColor3f(0.0f,1.0f,0.0f);      // Зеленный
        glVertex3f( 0.5f,-0.5f, -0.5f); // Лево треугольника (Сзади)
        glColor3f(0.0f,0.0f,1.0f);      // Синий
        glVertex3f(-0.5f,-0.5f, -0.5f); // Право треугольника (Сзади)

        // левая грань
        glColor3f(1.0f,0.0f,0.0f);      // Красный
        glVertex3f( 0.0f, 0.5f, 0.0f);  // Верх треугольника (Лево)
        glColor3f(0.0f,0.0f,1.0f);      // Синий
        glVertex3f(-0.5f,-0.5f,-0.5f);  // Лево треугольника (Лево)
        glColor3f(0.0f,1.0f,0.0f);      // Зеленный
        glVertex3f(-0.5f,-0.5f, 0.5f);  // Право треугольника (Лево)
    glEnd();    // Кончили рисовать пирамиду
    glFlush();

    glPopAttrib();
    glFlush();
}

void GL_WR::octahReshape(int Width, int Height)
{
    octahRender();
}

void GL_WR::octahSpecKeyboard(int key, int x, int y)
{
    switch(key)
    {
        case GLUT_KEY_F1:
            std::cout << "F1 is pressed\n";
            break;
        case GLUT_KEY_F10:
            std::cout << "F10 is pressed (exit)\n";
            exit(0x0);
            break;
        // case GLUT_KEY_SPAYCE
        default:
            std::cout << key << " is pressed" << "\n";
            break;
    }
    glutPostRedisplay();
}

void GL_WR::octahKeyboard(unsigned char key, int x, int y)
{
    switch (key) {
        case Keys::Esc:
            std::cout << "'Esc' is pressed (exit)\n";
            exit(0x0);
            break;
        case Keys::Space:
            std::cout << "'Space' is pressed (pause)\n";
            octah1.pause();
            break;
        default:
            unsigned int dd = key;
            cout << "U enter: " << key << " (" << dd << ")\n";
            break;
    }
    glutPostRedisplay();
}


void Octahedron::pause()
{
    if (isFrozen) {
        speedRot = stdSpeedRot;
        isFrozen = false;
    } else {
        speedRot = 0;
        isFrozen = true;
    }
}
