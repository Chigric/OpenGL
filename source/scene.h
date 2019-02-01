#ifndef SCENE_H
#define SCENE_H

#include <iostream>
#define M_PI 3.14159265358979323846
#include <math.h>
#include <list>

#include <GL/freeglut.h>

#include "octahedron.h"

namespace GL_WR {
	class Octahedron;
	extern Octahedron octah1;

	class Scene {

	private:
		void setGlutStaticFuncs();
		void initGlutStaticFuncs();
		void initGlut(int, char**);
		void lightInit();

		//WINDOW
		GLfloat WINDOW_X;
		GLfloat WINDOW_Y;
		GLfloat WIDTH_WINDOW;
	    GLfloat HEIGHT_WINDOW;
		GLfloat cur_resol;

		//FRAMES
	    static const unsigned int FRAME_IN_MSECS = 30;

		void (*specKeyboard)(int, int, int);
		void (*keyboard)(unsigned char, int, int);
		void (*reshape)(int, int);
		void (*render)(void);
		void (*timer)(int);

	public:
		Scene(int, char**);
		~Scene();

		static void printRule();

		static inline const unsigned int getFIMS() {
		    return FRAME_IN_MSECS;
		}
	};
}

#endif //SCENE_H
