#ifndef OCTAHEDRON_H
#define OCTAHEDRON_H

#include <GL/freeglut.h>
#include "global.h"
#include "octahedron.h"

namespace GL_WR {
	struct GLfloat2;
	struct GLfloat3;

	void octahTimer(int);
	void octahRender(void);
	void octahReshape(int, int);
	void octahSpecKeyboard(int, int, int);
	void octahKeyboard(unsigned char, int, int);

	class Octahedron {
		//Status
		bool isFrozen;

		//Parametres
		GLfloat height;
		GLfloat base_width;
		GLfloat base_length;

		//Angles
		GLfloat rotateY;
		GLfloat speedRot;
		GLfloat stdSpeedRot;
		
	private:
		void pause();

	public:
		Octahedron(GLfloat parametres);
		Octahedron(GLfloat base_parametres, GLfloat height);
		Octahedron(const GLfloat2&);
		Octahedron(GLfloat base_width, GLfloat base_length, GLfloat height);
		Octahedron(const GLfloat3&);

		friend void octahTimer(int);
		friend void octahRender(void);
		friend void octahReshape(int, int);
		friend void octahSpecKeyboard (int, int, int);
		friend void octahKeyboard(unsigned char, int, int);
	};
}

#endif //OCTAHEDRON_H
