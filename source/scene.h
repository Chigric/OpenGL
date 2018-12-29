#ifndef SCENE_H
#define SCENE_H

#include <iostream>
#define M_PI 3.14159265358979323846
#include <math.h>
#include <GL/freeglut.h>


namespace GL_WR {
	class Scene {

	private:
		void std_funcs();

		//WINDOW
		GLfloat WIDTH_WINDOW;
	    GLfloat HIEGHT_WINDOW;

		//FRAMES
	    static const unsigned int FRAME_IN_MSECS = 30;

		void (*render)(void);
		void (*reshape)(int, int);
		void (*timer)(int);

	public:
		Scene(int, char**);
		~Scene();
	};
}

#endif //SCENE_H
