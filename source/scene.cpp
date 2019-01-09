#include <GL/freeglut.h>

#include <list>
#include <functional>

#include "scene.h"
#include "global.h"

using namespace GL_WR;
using namespace std;

Scene::Scene(int argc, char **argv)
{
    //Initial window position
    WINDOW_X = 500;
    WINDOW_Y = 100;

    //Graphics display resolution
    //4 : 3
    WIDTH_WINDOW = 1000;
    cur_resol = (float)3/4;
    HEIGHT_WINDOW = WIDTH_WINDOW * cur_resol;

    //Glut functions fr create and setup window
    this->initGlut(argc, argv);

    //General funstions of scene
    this->initGlutStaticFuncs();

    //Start global timer (static function of glut)
	this->timer(0);

    glutMainLoop();
}

Scene::~Scene()
{}

void Scene::initGlutStaticFuncs()
{
    this->keyboard = &octahKeyboard;
    this->reshape = &octahReshape;
    this->render = &octahRender;
    this->timer = &octahTimer;

    this->setGlutStaticFuncs();
}

void Scene::setGlutStaticFuncs()
{
    //Glut std dinamic funcs
    glutDisplayFunc(this->render);
    glutReshapeFunc(this->reshape);
    glutSpecialFunc(this->keyboard);
}

void Scene::initGlut(int argc, char **argv)
{
    //Glut funcs
    glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowPosition(WINDOW_X, WINDOW_Y);
	glutInitWindowSize(WIDTH_WINDOW, HEIGHT_WINDOW);
	glutCreateWindow("Lab_OGL");
}
