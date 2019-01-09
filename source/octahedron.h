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
	void octahKeyboard(int, int, int);

	class Octahedron {
		GLfloat height;
		GLfloat base_width;
		GLfloat base_length;
	public:
		Octahedron(GLfloat);
		Octahedron(GLfloat, GLfloat);
		Octahedron(const GLfloat2&);
		Octahedron(GLfloat, GLfloat, GLfloat);
		Octahedron(const GLfloat3&);

		friend void octahTimer(int);
		friend void octahRender(void);
		friend void octahReshape(int, int);
		friend void octahKeyboard(int, int, int);
	};
}

#endif //OCTAHEDRON_H
