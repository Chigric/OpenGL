#include "scene.h"
#include <GL/freeglut.h>
#include "global.h"

using namespace GL_WR;

Scene::Scene(int argc, char **argv)
{
    //Graphics display resolution
    //4 : 3
    WIDTH_WINDOW = 1000;
    HIEGHT_WINDOW = 750;


    //Glut funcs
    glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowPosition(500, 100);
	glutInitWindowSize(WIDTH_WINDOW, HIEGHT_WINDOW);
	glutCreateWindow("Lab_OGL");

    //General funstions of scene
    this->std_funcs();

	glutDisplayFunc(this->render);
	glutReshapeFunc(this->reshape);

	this->timer(0);

	glutMainLoop();
}

Scene::~Scene()
{}

void Scene::std_funcs()
{
    this->reshape = &Reshape;
    this->render = &Render;
    this->timer = &Timer;
}
