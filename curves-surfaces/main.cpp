#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#include "curves.h"

#define PI 3.14159265
#define LARGURA_WINDOW 400
#define ALTURA_WINDOW  400
#define POSWX 250
#define POSWY 150

struct Ponto
{
    GLfloat x;
    GLfloat y;
    GLfloat z;
};

CurvePoints cp;
CurvePoints cp2;
Bezier bezier;
Hermite hermite;
Parabola parabola;


void init();
void draw();
void on_window_resize(GLsizei w, GLsizei h);
void on_keyboard_ev(unsigned char key, int x, int y);
void on_mouse_ev(int button, int state, int x, int y);
void draw_axis();

Ponto P1, P2, P3, P4;


int main(int argc, char *argv[])
{

    glutInit(&argc, argv);

    // Define do modo de opera��o da GLUT
    // GLUT_SINGLE significa que vai usar 1 buffer s� (se for usar anima��o ou 3D use GLUT_DOUBLE)
    // aqui, como o c�digo � 2D usamos 1 buffer
    // GLUT_RGB significa que cada pixel � RGB
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    // Especifica a posi��o inicial da janela GLUT
    glutInitWindowPosition(POSWX, POSWY);

    // Especifica o tamanho inicial em pixels da janela GLUT
    glutInitWindowSize(LARGURA_WINDOW, ALTURA_WINDOW);

    /* specify the display to be single
   buffered and color as RGBA values */

    // Cria a janela passando como argumento o t�tulo da mesma
    glutCreateWindow("Uma Bela Curva de Bezier de Grau 3");

    // Registra a fun��o callback de redesenho da janela de visualiza��o
    glutDisplayFunc(draw);

    // Registra a fun��o callback de redimensionamento da janela de visualiza��o
    glutReshapeFunc(on_window_resize);

    // Registra a fun��o callback para tratamento das teclas ASCII
    glutKeyboardFunc(on_keyboard_ev);

    // Registra a fun��o callback mouse
    glutMouseFunc(on_mouse_ev);

    // Chama a fun��o respons�vel por fazer as inicializa��es
    init();

    // Inicia o processamento e aguarda intera��es do usu�rio
    glutMainLoop();

    return 0;
}

void init()
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}


void draw()
{
    glClear(GL_COLOR_BUFFER_BIT);

    //hermite.draw(&cp2);
    bezier.draw(&cp);
    //parabola.draw();
    glFlush();
    //glutPostRedisplay();
}

void draw_axis()
{
    // Desenha a linha vertical
    glColor3f(0.0, 0.0f, 0.0f);
    glBegin(GL_LINES);
    glVertex2f(0.0f, Parabola::ltY);
    glVertex2f(0.0f, Parabola::gtY);
    glEnd();

    // Desenha a linha horizontal
    glColor3f(0.0, 0.0f, 0.0f);
    glBegin(GL_LINES);
    glVertex2f(Parabola::ltX, 0.0f);
    glVertex2f(Parabola::gtX, 0.0f);
    glEnd();

}

// Events callbacks

void on_window_resize(GLsizei w, GLsizei h)
{
    GLfloat width, height;

    if (h == 0) h = 1;

    width = w;
    height = h;

    // Especifica as dimens�es da Viewport
    glViewport(0, 0, width, height);

    // Inicializa o sistema de coordenadas
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if (width <= height)
        //gluOrtho2D(MENORX, MAIORX, MENORY*height / width, MAIORY*height / width);
        gluOrtho2D(Bezier::ltX, Bezier::gtX, Bezier::ltY*height / width, Bezier::gtY*height / width);
    else
        //gluOrtho2D(MENORX*width / height, MAIORX*width / height, MENORY, MAIORY);
        gluOrtho2D(Bezier::ltX*width / height, Bezier::gtX*width / height, Bezier::ltY, Bezier::gtY);
}

void on_keyboard_ev(unsigned char key, int x, int y)
{
    if (key == 27)// ESC
        exit(0);
}

void on_mouse_ev(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON) {
        //cp2.x = x; cp2.y = 400 - y;
        //hermite.get_points = 1;

        cp.x = x; cp.y = 400 - y;
        bezier.get_points = 1;
    } else if (button == GLUT_RIGHT_BUTTON) {
        bezier.get_points = 0;
        bezier.total_points = 0;

        //hermite.get_points = 0;
        //hermite.total_points = 0;
    }

    glutPostRedisplay();
}
