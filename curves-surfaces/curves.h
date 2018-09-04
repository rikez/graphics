#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>

#ifndef CURVES_SURFACES_CURVES_H
#define CURVES_SURFACES_CURVES_H

struct CurvePoints {
    GLfloat x;
    GLfloat y;
};

struct Bezier {
    GLfloat matrix[4][2];
    GLboolean get_points = 0;
    GLint total_points = 0;
    static GLfloat gtX;
    static GLfloat gtY;
    static GLfloat ltX;
    static GLfloat ltY;
    void draw(struct CurvePoints* cp);
    GLfloat multiply(GLfloat T[], GLfloat H[][4], GLfloat M[]);
};

struct Hermite {
    GLfloat matrix[2][4];
    GLboolean get_points = 0;
    GLint total_points = 0;
    static GLfloat tang1X;
    static GLfloat tang1Y;
    static GLfloat tang2X;
    static GLfloat tang2Y;
    void draw(struct CurvePoints* cp);
    // fun��o que multiplica as 3 matrizes de Hermite T * H * M, onde M = {X,Y}
    GLfloat multiply(GLfloat T[], GLfloat H[][4], GLfloat M[]);
};

struct Parabola {
    GLint degree = 2;
    GLfloat pace = 0.2;
    GLfloat a = 0.03;
    GLfloat b = 0;
    GLfloat c = -20;
    static GLfloat gtX;
    static GLfloat gtY;
    static GLfloat ltX;
    static GLfloat ltY;
    void draw();
};

#endif //CURVES_SURFACES_CURVES_H
