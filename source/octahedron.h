#ifndef OCTAHEDRON_H
#define OCTAHEDRON_H

#include <GL/freeglut.h>
#include "global.h"

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
		GLfloat3* autoRot;
		GLfloat3* lastAutoRot;
		GLfloat3* rotate;
		GLfloat3* speedRot;
		GLfloat stdAutoSpeedRot;
		GLfloat stdSpeedRot;

		//Vertex
		static const size_t qual_V = 6;
		static const size_t qual_side = 8;
		GLfloat *vertex;
		GLfloat *normal;
		GLfloat3 *color;
	    GLubyte *trigons;

		//Separation
		static const size_t Three_V = 3; //Потому что у нас треугольники (3 стороны)
		GLfloat *separation;
		GLfloat stdSpeedSeparation;

		//World
		const size_t dimension = 3;

		//Light
		GLfloat lightRot;
		GLfloat autoLightRot;
		GLfloat stdAutoLightRot;

		//Blend
		bool isBlend;

	private:
		void initVertex();
		void pause();
		void changeRot(GLfloat& axis, const GLfloat& direction);
		void autoRotate();
		void paint();
		void printTrigons(const GLfloat3& color);
		void printTrigons(	const GLfloat3& color1,
							const GLfloat3& color2,
							const GLfloat3& color3);
		void addSeparation();
		void deleteSeparation();
		void drawSphere();
		void getNormal();

		//Blend
		void setBlend();

	public:
		Octahedron(GLfloat parametres);
		Octahedron(GLfloat base_parametres, GLfloat height);
		Octahedron(const GLfloat2&);
		Octahedron(GLfloat base_width, GLfloat base_length, GLfloat height);
		Octahedron(const GLfloat3&);

		~Octahedron();

		friend void octahTimer(int);
		friend void octahRender(void);
		friend void octahReshape(int, int);
		friend void octahSpecKeyboard (int, int, int);
		friend void octahKeyboard(unsigned char, int, int);

		//Light
		void lightLeft();
		void lightRight();
	};
}

#endif //OCTAHEDRON_H
