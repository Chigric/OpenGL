#include <GL/freeglut.h>

#include <list>
#include <functional>

#include "scene.h"
#include "global.h"

using namespace GL_WR;
using namespace std;

Scene::Scene(int argc, char **argv)
{
    //Graphics display resolution
    //4 : 3
    cur_resol = 3/4;
    WIDTH_WINDOW = 1000;
    HIEGHT_WINDOW = WIDTH_WINDOW * 3/4;


    //Glut funcs
    glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowPosition(500, 100);
	glutInitWindowSize(WIDTH_WINDOW, HIEGHT_WINDOW);
	glutCreateWindow("Lab_OGL");

    //General funstions of scene
    this->std_funcs();

    //Glut std dinamic funcs
	glutDisplayFunc(this->render);
	glutReshapeFunc(this->reshape);
    glutSpecialFunc(this->keyboard);

	this->timer(0);

	glutMainLoop();
}

Scene::~Scene()
{}

void Scene::std_funcs()
{
    this->keyboard = &octahKeyboard;
    this->reshape = &octahReshape;
    this->render = &octahRender;
    this->timer = &octahTimer;

}
