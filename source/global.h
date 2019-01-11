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

        void init(const GLfloat3& ptr) {
            this->x = ptr.x;
            this->y = ptr.y;
            this->z = ptr.z;
        }
    };

    inline void color3f(const GLfloat3& color) {
        glColor3f(color.x, color.y, color.z);
    }

    inline void setColorBackground(const GLfloat3& color) {
        glClearColor(color.x, color.y, color.z, 1.0);
    }

    template<typename T>
    void setArray(T* array, const GLfloat3& ptr3) {
        size_t i = 0;
        array[i++] = ptr3.x;
        array[i++] = ptr3.y;
        array[i++] = ptr3.z;
    }

    enum Keys {Esc = 0x1b, Space = 0x20, A = 0x61, B, C, D, E, F, G, H, I, J, K,
        L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z, Brack_L = 0x5b, Brack_R = 0x5d};

    //COLORS
    const GLfloat3 black = {0.0, 0.0, 0.0};
    const GLfloat3 red = {1.0, 0.0, 0.0};
    const GLfloat3 orangered = {1.0, 0.27, 0.0};
    const GLfloat3 green = {0.0, 1.0, 0.0};
    const GLfloat3 yellow = {1.0, 1.0, 0.0};
    const GLfloat3 amber = {1.0, 0.749, 0.0};
    const GLfloat3 blue = {0.0, 0.0, 1.0};
    const GLfloat3 magenta = {1.0, 0.0, 1.0};
    const GLfloat3 cyan = {0.0, 1.0, 1.0};
    const GLfloat3 white = {1.0, 1.0, 1.0};
    const GLfloat3 brown = {0.588, 0.294, 0.0};
    const GLfloat3 pink = {1.0, 0.753, 0.796};
    const GLfloat3 lightPink = {1.0, 0.714, 0.757};
    const GLfloat3 hotPink = {1.0, 0.412, 0.706};
    const GLfloat3 deepPink = {1.0, 0.078, 0.576};
    const GLfloat3 palevioletred = {0.859, 0.439, 0.576};
    const GLfloat3 mediumvioletred = {0.780, 0.082, 0.522};
}

#endif //GLOBAL_H
