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

    autoRotX = 0;
    autoRotY = 0;
    autoRotZ = 0;

    lastAutoRot = new GLfloat3;
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
    delete lastAutoRot;

    delete rotate;
    delete speedRot;

    delete color;
    delete vertex;
}

void Octahedron::initVertex()
{
    //Color
    color = new GLfloat[qual_V*3];
    setArray(&color[0],		white);
    setArray(&color[3],		yellow);
    setArray(&color[6],		green);
    setArray(&color[9],		brown);
    setArray(&color[12],	amber);
    setArray(&color[15],	magenta);

    //Vertex
    vertex = new GLfloat[qual_V*3];
    setArray(&vertex[0],	{0.0, height, 0.0});
    setArray(&vertex[3],	{base_length/2, 0.0, base_width/2});
    setArray(&vertex[6],	{-base_length/2, 0.0, -base_width/2});
    setArray(&vertex[9],	{base_length/2, 0.0, -base_width/2});
    setArray(&vertex[12],	{-base_length/2, 0.0, base_width/2});
    setArray(&vertex[15],	{0.0, -height, 0.0});

    //Indexes
    trigons = new GLubyte*[qual_side];
    for (size_t i = 0; i < qual_side; i++) {
        trigons[i] = new GLubyte[3];
    }
    setArray(trigons[0], {0, 4, 1});
    setArray(trigons[1], {0, 1, 3});
    setArray(trigons[2], {0, 3, 2});
    setArray(trigons[3], {0, 2, 4});

    setArray(trigons[4], {5, 4, 1});
    setArray(trigons[5], {5, 1, 3});
    setArray(trigons[6], {5, 3, 2});
    setArray(trigons[7], {5, 2, 4});
}

void Octahedron::printTrigons(size_t ind, const GLfloat3& color)
{
    color3f(color);
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, trigons[ind]);
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
    glLoadIdentity();   // Сброс просмотра
    // glTranslatef(-octah1.base_length/2, -octah1.height/2, 0.0f); // Сдвиг влево экрана

    glRotatef(rotate->x, 1, 0, 0);// Вращение треугольников по оси X
    glRotatef(rotate->y, 0, 1, 0);// Вращение треугольников по оси Y
    glRotatef(rotate->z, 0, 0, 1);// Вращение треугольников по оси Z

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertex);

    printTrigons(0, blue);
    printTrigons(1, green);
    printTrigons(2, yellow);
    printTrigons(3, cyan);
    printTrigons(4, amber);
    printTrigons(5, magenta);
    printTrigons(6, red);
    printTrigons(7, brown, white, black);

    glEnableClientState(GL_VERTEX_ARRAY);
}

void Octahedron::pause()
{
    if (isFrozen) {
        std::cout << "\n\tstart\n";
        isFrozen = false;
        autoRotX = lastAutoRot->x;
        autoRotY = lastAutoRot->y;
        autoRotZ = lastAutoRot->z;
    } else {
        std::cout << "\n\tstop\n";
        isFrozen = true;
        lastAutoRot->init({autoRotX, autoRotY, autoRotZ});
        autoRotX = 0;
        autoRotY = 0;
        autoRotZ = 0;
    }

    if (autoRotX || autoRotY || autoRotZ)
        isFrozen = false;
}

void Octahedron::autoRotate()
{
    //Logic
    cout << "It's octahedron is frozen: " << isFrozen << "\n";

    if (!isFrozen) {
        speedRot->x = (autoRotX*stdSpeedRot);
        speedRot->y = (autoRotY*stdSpeedRot);
        speedRot->z = (autoRotZ*stdSpeedRot);
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
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Очистка экрана и буфера глубины

    // glPushAttrib(GL_LINE_BIT);
    // glClear(GL_COLOR_BUFFER_BIT);

    //Paint
    octah1.paint();

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
        case Keys::S:
            std::cout << "'S' is pressed: ";
            octah1.autoRotY = (octah1.autoRotY < 0) ? 0 : -1;
            octah1.isFrozen = (octah1.isFrozen) ? false : true;
            break;
        case Keys::W:
            std::cout << "'W' is pressed: ";
            octah1.autoRotY = (octah1.autoRotY > 0) ? 0 : 1;
            octah1.isFrozen = (octah1.isFrozen) ? false : true;
            break;
        case Keys::A:
            std::cout << "'W' is pressed (pause): ";
            octah1.autoRotX = (octah1.autoRotX != 0) ? -1 : 0;
            break;
        case Keys::D:
            std::cout << "'W' is pressed (pause): ";
            octah1.autoRotX = (octah1.autoRotX != 0) ? 1 : 0;
            break;
        case Keys::Z:
            std::cout << "'Z' is pressed (pause): ";
            octah1.autoRotZ = (octah1.autoRotZ != 0) ? -1 : 0;
            break;
        case Keys::X:
            std::cout << "'X' is pressed (pause): ";
            octah1.autoRotZ = (octah1.autoRotZ != 0) ? 1 : 0;
        default:
            unsigned int dd = key;
            cout << "U enter: " << key << " (" << dd << ")\n";
            break;
    }
    glutPostRedisplay();
}
