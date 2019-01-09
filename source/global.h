#ifndef GLOBAL_H
#define GLOBAL_H

#include <GL/freeglut.h>
#include <iostream>

#include "scene.h"

namespace GL_WR {
    class Scene;

    struct GLfloat2 {
        GLfloat x;
        GLfloat y;
    };

    struct GLfloat3 {
        GLfloat x;
        GLfloat y;
        GLfloat z;
    };

    inline void color3f(const GLfloat3& color)
    {
        glColor3f(color.x, color.y, color.z);
    }

    inline void setColorBackground(const GLfloat3& color)
    {
        glClearColor(color.x, color.y, color.z, 1.0);
    }

    //COLORS
    const GLfloat3 black = {0.0, 0.0, 0.0};
    const GLfloat3 red = {1.0, 0.0, 0.0};
    const GLfloat3 green = {0.0, 1.0, 0.0};
    const GLfloat3 yellow = {1.0, 1.0, 0.0};
    const GLfloat3 amber = {1.0, 0.749, 0.0};
    const GLfloat3 blue = {0.0, 0.0, 1.0};
    const GLfloat3 magenta = {1.0, 0.0, 1.0};
    const GLfloat3 cyan = {0.0, 1.0, 1.0};
    const GLfloat3 white = {1.0, 1.0, 1.0};
    const GLfloat3 brown = {0.588, 0.294, 0.0};
}

#endif //GLOBAL_H
