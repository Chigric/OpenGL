#ifndef SCENE_H
#define SCENE_H

#include <iostream>
#define M_PI 3.14159265358979323846
#include <math.h>
#include <list>

#include <GL/freeglut.h>

#include "octahedron.h"

namespace GL_WR {
	class Scene {

	private:
		void std_funcs();

		//WINDOW
		GLfloat WIDTH_WINDOW;
	    GLfloat HIEGHT_WINDOW;
		GLfloat cur_resol;

		//FRAMES
	    static const unsigned int FRAME_IN_MSECS = 30;

		void (*keyboard)(int, int, int);
		void (*reshape)(int, int);
		void (*render)(void);
		void (*timer)(int);

	public:
		Scene(int, char**);
		~Scene();
	};
}

#endif //SCENE_H
