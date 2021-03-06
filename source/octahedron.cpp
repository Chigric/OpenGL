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
    rotate->init({-10, 22.5, 0});

    this->autoRot = new GLfloat3;
    autoRot->init({0, 0, 0});

    this->lastAutoRot = new GLfloat3;
    lastAutoRot->init({0, 0, 0});

    //Default speed of Agels
    this->stdAutoSpeedRot = 2.5f;
    this->stdSpeedRot = 2.5f;

    //Speed of Agels
    this->speedRot = new GLfloat3;
    speedRot->init({0, 0, 0});

    //Status
    this->isFrozen = true;

    initVertex();

    //Separation
    this->stdSpeedSeparation = 0.025f;
    this->separation = new GLfloat[Three_V];
    setArray(separation, {0, 0, 0});

    addSeparation();

    //Light
    this->lightRot = 0;
    autoLightRot = 0;
    this->stdAutoLightRot = 4;

    //Blend
    this->isBlend = false;
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

    delete[] color;
    delete[] vertex;
    delete[] trigons;
    delete[] normal;

    delete[] separation;
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
    vertex = new GLfloat[Three_V*dimension];
    setArray(&vertex[0],	{0.0, height, 0.0});                   //0
    setArray(&vertex[3],	{base_length/2, 0.0, base_width/2});   //1
    setArray(&vertex[6],	{-base_length/2, 0.0, base_width/2});  //2

    //Indexes
    trigons = new GLubyte[Three_V];
    setArray(trigons, {0, 1, 2});

    //Normal
    normal = new GLfloat[Three_V*dimension];
    for (size_t i = 0; i < Three_V*dimension; i+=Three_V)
        setArray(&normal[i],	{0.0, 0.0, 0.0});
}

void Octahedron::addSeparation()
{
    GLfloat tmp[dimension];
    setArray(tmp, {0, 0, 0});
    for (size_t i = 0; i < Three_V; i++) {
        for (size_t j = 0; j < Three_V; j++) {
            tmp[i] += vertex[trigons[j] * Three_V + i];
        }

        if (tmp[i] < 0.f)
            separation[i] = -stdSpeedSeparation;
        else if (tmp[i] == 0.f)
            separation[i] = 0.f;
        else
            separation[i] = stdSpeedSeparation;

        for (size_t k = 0; k < dimension; k++)
            vertex[trigons[k] * Three_V + i] += separation[i];
    }
}

void Octahedron::deleteSeparation()
{
    for (size_t i = 0; i < Three_V; i++) {
        for (size_t k = 0; k < dimension; k++)
            vertex[trigons[k] * Three_V + i] -= separation[i];
    }
}

void Octahedron::printTrigons(const GLfloat3& color)
{
    color3f(color);
    glDrawElements(GL_TRIANGLES, dimension, GL_UNSIGNED_BYTE, trigons);
}

void Octahedron::printTrigons(  const GLfloat3& color1,
                                const GLfloat3& color2,
                                const GLfloat3& color3)
{
    glBegin(GL_TRIANGLES);
        color3f(color1);
        glArrayElement(trigons[0]);
        color3f(color2);
        glArrayElement(trigons[1]);
        color3f(color3);
        glArrayElement(trigons[2]);
    glEnd();
}

void Octahedron::getNormal()
{
    float v1[3], v2[3]; // для промежуточных вычислений
    float l; // норма

    v1[0] = vertex[3]- vertex[0];
    v1[1] = vertex[4]- vertex[1];
    v1[2] = vertex[5]- vertex[2];

    v2[0] = vertex[6]- vertex[0];
    v2[1] = vertex[7]- vertex[1];
    v2[2] = vertex[8]- vertex[2];

    normal[0] = v1[1] * v2[2] - v1[2] * v2[1];
    normal[1] = v1[2] * v2[0] - v1[0] * v2[2];
    normal[2] = v1[0] * v2[1] - v1[1] * v2[0];

    l = sqrt(normal[0]*normal[0] + normal[1]*normal[1] + normal[2]*normal[2]);
    // нормирование
    normal[0] /= l;
    normal[1] /= l;
    normal[2] /= l;

    for (size_t i = 0; i < Three_V; i++)
        normal[i+6] = normal[i+3] = normal[i];
}

void Octahedron::paint()
{
    glRotatef(rotate->x, 1, 0, 0);// Вращение треугольников по оси X
    glRotatef(rotate->y, 0, 1, 0);// Вращение треугольников по оси Y
    glRotatef(rotate->z, 0, 0, 1);// Вращение треугольников по оси Z

    getNormal();

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glVertexPointer(dimension, GL_FLOAT, 0, vertex);
    glNormalPointer(GL_FLOAT, 0, normal);

    GLfloat angel = 0.0f;
    for(size_t i = 0; i < qual_side; i++) {
        glPushMatrix();
            glRotatef(angel, 0.0, 1.0, 0.0);
            if (i == qual_side-1)
                printTrigons(color[qual_side-1],
                            color[qual_side+0], color[qual_side+1]);
            else
                printTrigons(color[i]);
        glPopMatrix();
        if (angel == 270) {
            glRotatef(180, 0.0, 0.0, 1.0);
            angel = 0;
        } else {
            angel += 90;
        }
    }

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
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
    if (!isFrozen) {
        speedRot->x = (autoRot->x*stdAutoSpeedRot);
        speedRot->y = (autoRot->y*stdAutoSpeedRot);
        speedRot->z = (autoRot->z*stdAutoSpeedRot);
    } else
        speedRot->init({0,0,0});

    //Переменная вращения
    rotate->x += speedRot->x;
    rotate->y += speedRot->y;
    rotate->z += speedRot->z;

    //Light
    lightRot += (autoLightRot*stdAutoLightRot);
}

void Octahedron::drawSphere()
{
    color3f(white);
    glRotatef(lightRot, 0, 1, 0);
    glTranslatef(0.0f, 0.f, -0.75);
    glutSolidSphere(0.05, 25, 25);

    float lightpos[] = {0, 0, 0.75, 0};
    glLightfv(GL_LIGHT0, GL_POSITION, lightpos);
}

void Octahedron::lightLeft()
{
    changeRot(autoLightRot, 1);
}

void Octahedron::lightRight()
{
    changeRot(autoLightRot, -1);
}

void Octahedron::setBlend()
{
    if (isBlend)
    {
        glEnable(GL_BLEND);
        glDepthMask(GL_FALSE);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    }
    else
    {
        glDepthMask(GL_TRUE);
        glDisable(GL_BLEND);
    }
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

    // свойства материала
    GLfloat material_diffuse[] = {1.0, 1.0, 1.0, 1.0};
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material_diffuse);

    octah1.setBlend();

    glEnable(GL_LIGHT0);

    glPushMatrix();
    //Light
        octah1.drawSphere();
    glPopMatrix();

    // glPushAttrib(GL_LINE_BIT);

    // glDepthFunc(GL_EQUAL);
    // glEnable(GL_CULL_FACE);
    // glCullFace(GL_BACK);
    // glFrontFace(GL_CCW); //Она стоит по умолчанию, так что нет смысла её юзать

    glPushMatrix();
    //Paint
        octah1.paint();
    glPopMatrix();


    glDisable(GL_LIGHT0);
    // glEnable(GL_LIGHTING);
    glutSwapBuffers();

    // glPopAttrib();
    // glFlush();
}

void GL_WR::octahReshape(int Width, int Height)
{
    // glViewport(0, 0, 1000, 750);
    // gluOrtho2D(0, 1000, 0, 750);
    // gluOrtho2D(0, 1, 0, 0.75);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    octahRender();
}

void GL_WR::octahSpecKeyboard(int key, int x, int y)
{
    switch(key)
    {
        case GLUT_KEY_F1:
            std::cout << "F1 is pressed (help)\n";
            GL_WR::Scene::printRule();
            break;
        case GLUT_KEY_F2:
            // std::cout << "F2 is pressed\n";
            if (octah1.vertex[1] < (octah1.height * 2.5f))
                octah1.addSeparation();
            break;
        case GLUT_KEY_F3:
            // std::cout << "F3 is pressed\n";
            if (octah1.vertex[1] > octah1.height)
                octah1.deleteSeparation();
            break;
        case GLUT_KEY_F4:
            octah1.lightLeft();
            break;
        case GLUT_KEY_F5:
            octah1.lightRight();
            break;
        case GLUT_KEY_F8:
            octah1.isBlend = (octah1.isBlend) ? false : true;
            break;
        case GLUT_KEY_F10:
            std::cout << "F10 is pressed (exit)\n";
            exit(0x0);
            break;
        case GLUT_KEY_RIGHT:
            octah1.rotate->y -= octah1.stdSpeedRot;
            break;
        case GLUT_KEY_LEFT:
            octah1.rotate->y += octah1.stdSpeedRot;
            break;
        case GLUT_KEY_UP:
            octah1.rotate->x -= octah1.stdSpeedRot;
            break;
        case GLUT_KEY_DOWN:
            octah1.rotate->x += octah1.stdSpeedRot;
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
            // std::cout << "'W' is pressed: ";
            octah1.changeRot(octah1.autoRot->x, -1);
            break;
        case Keys::S:
            // std::cout << "'S' is pressed: ";
            octah1.changeRot(octah1.autoRot->x, 1);
            break;
        case Keys::D:
            // std::cout << "'D' is pressed (pause): ";
            octah1.changeRot(octah1.autoRot->y, -1);
            break;
        case Keys::A:
            // std::cout << "'W' is pressed (pause): ";
            octah1.changeRot(octah1.autoRot->y, 1);
            break;
        case Keys::Z:
            // std::cout << "'Z' is pressed (pause): ";
            octah1.changeRot(octah1.autoRot->z, -1);
            break;
        case Keys::X:
            // std::cout << "'X' is pressed (pause): ";
            octah1.changeRot(octah1.autoRot->z, 1);
        case Keys::Brack_R:
            octah1.rotate->z -= octah1.stdSpeedRot;
            break;
        case Keys::Brack_L:
            octah1.rotate->z += octah1.stdSpeedRot;
            break;
        default:
            unsigned int dd = key;
            cout << "U enter: " << key << " (" << dd << ")\n";
            break;
    }
    glutPostRedisplay();
}
