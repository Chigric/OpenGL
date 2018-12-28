#include <stdio.h>
#define M_PI 3.14159265358979323846
#include <math.h>
#include <GL/freeglut.h>

namespace GL_WR {
    struct GLfloat3 {
        GLfloat _x;
        GLfloat _y;
        GLfloat _z;
    };

    //Graphics display resolution
    //4 : 3
    const GLfloat WIDTH_WINDOW = 1000;
    const GLfloat HIEGHT_WINDOW = 750;

    //FRAME IN MSECS
    GLfloat FRAME_IN_MSECS = 30;

    //Colors
    GLfloat3 black = {0.0, 0.0, 0.0};
    GLfloat3 red = {1.0, 0.0, 0.0};
    GLfloat3 green = {0.0, 1.0, 0.0};
    GLfloat3 yellow = {1.0, 1.0, 0.0};
    GLfloat3 amber = {1.0, 0.749, 0.0};
    GLfloat3 blue = {0.0, 0.0, 1.0};
    GLfloat3 magenta = {1.0, 0.0, 1.0};
    GLfloat3 cyan = {0.0, 1.0, 1.0};
    GLfloat3 white = {1.0, 1.0, 1.0};
    GLfloat3 brown = {0.588, 0.294, 0.0};

    inline void color3f(GLfloat3 color)
    {glColor3f(color._x, color._y, color._z);}

    struct GLfloat2 {
        GLfloat _x;
        GLfloat _y;
    };

    struct Circle {
        int accuracy;
        GLfloat radius;
        GLfloat2 pos;
        GLfloat3 color;

        //c-tor
        Circle() {
            this->pos = {0.f, 0.f};
            this->radius = 0;
            this->accuracy = 0;
            this->color = black;
        }

        Circle(GLfloat3 color, GLfloat2 pos, GLfloat radius, int accuracy) {
            this->color = color;
            this->pos = pos;
            this->radius = radius;
            this->accuracy = accuracy;
        }

        //Draw
        void drawCircle(int draw_part = 1,
                        GLfloat multy_x = 1.f, GLfloat multy_y = 1.f,
                        GLfloat plus_x = 0.f, GLfloat plus_y = 0.f,
                        GLfloat trans_cent_x = 0.f, GLfloat trans_cent_y = 0.f) {
            color3f(color);
            GLfloat __plus_x = 0.f;
            GLfloat __plus_y = 0.f;

            glBegin(GL_TRIANGLE_FAN);
                glVertex2f(pos._x + trans_cent_x, pos._y + trans_cent_y);
                for(int i = 0; i <= accuracy / draw_part + 1; i++) {
                    GLfloat t__ = i * 2*M_PI / accuracy;
                    glVertex2f(pos._x + radius * cos(t__) * multy_x + __plus_x,
                               pos._y + radius * sin(t__) * multy_y + __plus_y
                               );
                    __plus_x += plus_x;
                    __plus_y += plus_y;
                }
            glEnd();
        }
    };

    void primRectangle(GLfloat2 pos_st, GLfloat2 pos_end, bool isFill) {
        if (isFill) {
            glBegin(GL_POLYGON);
                glVertex2f(pos_st._x, pos_st._y);
                glVertex2f(pos_end._x, pos_st._y);
                glVertex2f(pos_end._x, pos_end._y);
                glVertex2f(pos_st._x, pos_end._y);
            glEnd();
        } else {
            glBegin(GL_LINE_LOOP);
                glVertex2f(pos_st._x, pos_st._y);
                glVertex2f(pos_end._x, pos_st._y);
                glVertex2f(pos_end._x, pos_end._y);
                glVertex2f(pos_st._x, pos_end._y);
            glEnd();
        }
    }

    void primRectangle(GLfloat2 pos_st, GLfloat diff, bool isFill) {
        primRectangle(pos_st, {pos_st._x+diff, pos_st._y+diff}, isFill);
    }
}

using namespace GL_WR;


GL_WR::Circle Sun({1.f, 0.75, 0.15f}, {800.f, 650.f}, 50.f, 50);

bool newDay = true;

inline void setSkyColor(GL_WR::GLfloat3& color)
{
    glClearColor(color._x, color._y, color._z, 1.0);
}


void Init(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_SINGLE | GLUT_RGBA);
/*
	GLUT_RGBA или GLUT_RGB - выбирает окно RGBA.
    GLUT_INDEX - выбирает режим индексированного цвета.
    Режим отображения также позволяет выбрать одно-или двухместных буфера окна. Предопределенные константы для этого являются:
    GLUT_SINGLE - режим одинарной буферизации.
    GLUT_DOUBLE - режим двойной буферизации, - РЕЖИМ, ПОДХОДЯЩИЙ ДЛЯ АНИМАЦИИ.
    Также существуют специализированные режимы буфера:
    GLUT_ACCUM - буфер накопления.
    GLUT_STENCIL - Буфер трафарета.
    GLUT_DEPTH -буфер глубины.
*/
	glutInitWindowPosition(500,100);
	glutInitWindowSize(WIDTH_WINDOW, HIEGHT_WINDOW);
	glutCreateWindow("Lab_1");

	setSkyColor(GL_WR::black);
}

void renderScene(void) {
    glClear(GL_COLOR_BUFFER_BIT);

    glPushAttrib(GL_LINE_BIT);


    //House
    GL_WR::GLfloat2 house_st = {100.0, 50.0};
    GLfloat house_diff = 400;
    GL_WR::color3f(GL_WR::brown);
    GL_WR::primRectangle(house_st, house_diff, true);


    //Window
    GLfloat window_diff = house_diff/4;
    GL_WR::GLfloat2 window_st = {
        house_st._x + house_diff/2 - window_diff/2,
        house_st._y + house_diff/2 - window_diff/2
        };
    GL_WR::color3f(GL_WR::amber);
    GL_WR::primRectangle(window_st, window_diff, true);

    //Frame of Window
    GL_WR::color3f(GL_WR::white);
    GL_WR::primRectangle(window_st, window_diff, false);
    glBegin(GL_LINES);
        glVertex2d(window_st._x + window_diff/2, window_st._y);
        glVertex2d(window_st._x + window_diff/2, window_st._y + window_diff);
        glVertex2d(window_st._x, window_st._y + window_diff/2);
        glVertex2d(window_st._x + window_diff, window_st._y + window_diff/2);
    glEnd();


    //Sun
    GL_WR::Circle sun = Sun;
    sun.drawCircle();


    //Earth
    GL_WR::GLfloat2 earth_st = {50.f, 0.f};
    GL_WR::GLfloat2 earth_end = {WIDTH_WINDOW - 75, house_st._y};
    GL_WR::color3f(GL_WR::green);
    GL_WR::primRectangle(earth_st, earth_end, true);

    //Earth Left
    GL_WR::Circle earthLeft(GL_WR::green, earth_st, earth_end._y, 50);
    earthLeft.drawCircle(4, -1.f);

    //Earth Right
    GL_WR::Circle earthRight(GL_WR::green, earth_end,
                             (100 + WIDTH_WINDOW - earth_end._x), 100);
    earthRight.drawCircle(2, 1.f, 1.f, 0.f, -5.f, -150.f);

//    GLfloat earth_3_radius = 100 + WIDTH_WINDOW - earth_end._x;
//    int earth_3_accuracy = 100;

    //Earth Right - Down
    GL_WR::GLfloat2 earth_4_st = earth_st;
    GL_WR::GLfloat2 earth_4_end = {WIDTH_WINDOW, house_st._y};
    GL_WR::color3f(GL_WR::green);
    GL_WR::primRectangle(earth_4_st, earth_4_end, true);

	glPopAttrib();
    glFlush();
}

void Reshape(int Width, int Height)
{
	if (Height == 0) {
		Height = 1;
	}

	glViewport(0, 0, (GLsizei)Width, (GLsizei)Height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, (GLdouble)Width, 0.0, (GLdouble)Height);


	renderScene();
}

void Timer(int iUnused)
{
    //Logic
    if (Sun.pos._x <= -Sun.radius) {
        Sun.pos._x = WIDTH_WINDOW + Sun.radius;
        if (newDay) {
            setSkyColor(GL_WR::blue);
            newDay = false;
            Sun.color = GL_WR::yellow;
        } else {
            setSkyColor(GL_WR::black);
            newDay = true;
            Sun.color = {1.f, 0.85, 0.f};
        }
    } else {
        if ((Sun.pos._x > WIDTH_WINDOW/2 - 200) &&
            (Sun.pos._x < WIDTH_WINDOW - 200) )
            Sun.pos._y += 1;
        else
            Sun.pos._y -= 1;
        Sun.pos._x -= 10;
    }

    glutPostRedisplay();
    glutTimerFunc(FRAME_IN_MSECS, Timer, 0);
}

int main(int argc, char **argv) {
    // инициализация
    Init(argc, argv);

	// регистрация обратных вызовов
	glutDisplayFunc(renderScene);
	glutReshapeFunc(Reshape);

	// Запуск Таймера
	Timer(0);

	// Основной цикл GLUT
	glutMainLoop();

	return 1;
}
