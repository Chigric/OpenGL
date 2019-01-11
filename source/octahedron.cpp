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
    this->rotate = new GLfloat3;
    rotate->init({0, 0, 0});

    this->autoRot = new GLfloat3;
    autoRot->init({0, 0, 0});

    this->lastAutoRot = new GLfloat3;
    lastAutoRot->init({0, 0, 0});

    //Default speed of Agels
    this->stdSpeedRot = 0.8f;

    //Speed of Agels
    this->speedRot = new GLfloat3;
    speedRot->init({0, 0, 0});

    //Status
    this->isFrozen = true;

    initVertex();
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

Octahedron::~Octahedron()
{
    delete autoRot;
    delete lastAutoRot;

    delete rotate;
    delete speedRot;

    delete color;
    delete vertex;
}

void Octahedron::initVertex()
{
    //Color
    color = new GLfloat3[qual_side+2];
    color[0].init(green);
    color[1].init(blue);
    color[2].init(yellow);
    color[3].init(cyan);
    color[4].init(amber);
    color[5].init(magenta);
    color[6].init(red);
    color[7].init(brown);
    color[8].init(deepPink);
    color[9].init(black);

    //Vertex
    vertex = new GLfloat[qual_V*dimension];
    setArray(&vertex[0],	{0.0, height, 0.0});
    setArray(&vertex[3],	{base_length/2, 0.0, base_width/2});
    setArray(&vertex[6],	{-base_length/2, 0.0, -base_width/2});
    setArray(&vertex[9],	{base_length/2, 0.0, -base_width/2});
    setArray(&vertex[12],	{-base_length/2, 0.0, base_width/2});
    setArray(&vertex[15],	{0.0, -height, 0.0});

    //Indexes
    trigons = new GLubyte*[qual_side];
    for (size_t i = 0; i < qual_side; i++) {
        trigons[i] = new GLubyte[dimension];
    }
    setArray(trigons[0], {0, 4, 1});
    setArray(trigons[1], {0, 1, 3});
    setArray(trigons[2], {0, 3, 2});
    setArray(trigons[3], {0, 2, 4});

    setArray(trigons[7], {5, 2, 4});
    setArray(trigons[6], {5, 3, 2});
    setArray(trigons[5], {5, 1, 3});
    setArray(trigons[4], {5, 4, 1});
}

void Octahedron::printTrigons(size_t ind, const GLfloat3& color)
{
    color3f(color);
    glDrawElements(GL_TRIANGLES, dimension, GL_UNSIGNED_BYTE, trigons[ind]);
}

void Octahedron::printTrigons( size_t ind,
                            const GLfloat3& color1,
                            const GLfloat3& color2,
                            const GLfloat3& color3)
{
    glBegin(GL_TRIANGLES);
        color3f(color1);
        glArrayElement(trigons[ind][0]);
        color3f(color2);
        glArrayElement(trigons[ind][1]);
        color3f(color3);
        glArrayElement(trigons[ind][2]);
    glEnd();
}

void Octahedron::paint()
{
    // glTranslatef(-octah1.base_length/2, -octah1.height/2, 0.0f); // Сдвиг влево экрана

    glRotatef(rotate->x, 1, 0, 0);// Вращение треугольников по оси X
    glRotatef(rotate->y, 0, 1, 0);// Вращение треугольников по оси Y
    glRotatef(rotate->z, 0, 0, 1);// Вращение треугольников по оси Z

    // glTranslatef(0.0, 0, 0.5f);

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(dimension, GL_FLOAT, 0, vertex);

    for(size_t i = 0; i < qual_side-1; i++) {
        printTrigons(i, color[i]);
    }

    printTrigons(qual_side-1, color[qual_side-1],
                    color[qual_side+0], color[qual_side+1]);

    glEnableClientState(GL_VERTEX_ARRAY);
}

void Octahedron::pause()
{
    if (isFrozen) {
        std::cout << "\n\tstart\n";
        isFrozen = false;
        autoRot->init(*lastAutoRot);
    } else {
        std::cout << "\n\tstop\n";
        isFrozen = true;
        lastAutoRot->init(*autoRot);
        autoRot->init({0, 0, 0});
    }

    if (autoRot->x || autoRot->y || autoRot->z)
        isFrozen = false;
}

void Octahedron::changeRot(GLfloat& axis, const GLfloat& direction)
{
    if ( (direction * axis) > 0 ) {
        axis = 0;
        isFrozen = true;

        if (autoRot->x || autoRot->y || autoRot->z)
            isFrozen = false;
    } else {
        axis = direction;
        isFrozen = false;
    }
}

void Octahedron::autoRotate()
{
    //Logic
    cout << "It's octahedron is frozen: " << isFrozen << "\n";

    if (!isFrozen) {
        speedRot->x = (autoRot->x*stdSpeedRot);
        speedRot->y = (autoRot->y*stdSpeedRot);
        speedRot->z = (autoRot->z*stdSpeedRot);
    } else
        speedRot->init({0,0,0});

    //Переменная вращения
    rotate->x += speedRot->x;
    rotate->y += speedRot->y;
    rotate->z += speedRot->z;
}

void GL_WR::octahTimer(int iUnused)
{
    octah1.autoRotate();

    glutPostRedisplay();
    glutTimerFunc(GL_WR::Scene::getFIMS(), octahTimer, 0);
}

void GL_WR::octahRender(void) {
    // Очистка экрана и буфера глубины
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // glPushAttrib(GL_LINE_BIT);

    glEnable(GL_DEPTH_TEST);
    // glDepthFunc(GL_EQUAL);
    // glEnable(GL_CULL_FACE);
    // glCullFace(GL_BACK);
    // glFrontFace(GL_CCW); //Она стоит по умолчанию, так что нет смысла её юзать

    glLoadIdentity();   // Сброс просмотра

    //Paint
    octah1.paint();

    glDisable(GL_DEPTH_TEST);
    // glDisable(GL_CULL_FACE);

    // glPopAttrib();
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
            std::cout << "'Space' is pressed (pause): ";
            octah1.pause();
            break;
        case Keys::W:
            std::cout << "'W' is pressed: ";
            octah1.changeRot(octah1.autoRot->x, -1);
            break;
        case Keys::S:
            std::cout << "'S' is pressed: ";
            octah1.changeRot(octah1.autoRot->x, 1);
            break;
        case Keys::A:
            std::cout << "'W' is pressed (pause): ";
            octah1.changeRot(octah1.autoRot->y, -1);
            break;
        case Keys::D:
            std::cout << "'W' is pressed (pause): ";
            octah1.changeRot(octah1.autoRot->y, 1);
            break;
        case Keys::Z:
            std::cout << "'Z' is pressed (pause): ";
            octah1.changeRot(octah1.autoRot->z, -1);
            break;
        case Keys::X:
            std::cout << "'X' is pressed (pause): ";
            octah1.changeRot(octah1.autoRot->z, 1);
        default:
            unsigned int dd = key;
            cout << "U enter: " << key << " (" << dd << ")\n";
            break;
    }
    glutPostRedisplay();
}
