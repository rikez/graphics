#include <stdio.h>
#include <stdlib.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#include <math.h>

#define MAIORX  50.0f
#define MENORX -50.0f
#define MAIORY  50.0f
#define MENORY -50.0f

#define WIDTH 400
#define HEIGHT 400
#define POSWX 250
#define POSWY 150
#define PI 3.141592
#define ANGLE 30


void init();
void multiply(GLfloat A[][4], GLfloat B[][4], GLfloat M[][4]);
void display_square();
void display_axis();
void draw();
void on_resize(GLsizei w, GLsizei h);
void on_key_press(unsigned char key, int x, int y);
void on_mouse_ev(int bt, int state, int x, int y);
void calc(GLfloat m_translate[][4], struct Point *origin);
void translate(struct Point *origin, float x, float y);
void rotate(struct Point *origin, GLfloat x, GLfloat y, GLfloat angle);
void apply_size();

struct Point
{
    GLfloat x; GLfloat y; GLfloat z;
};

struct Square
{
    Point pt[4];
};
Square sq;


int main(int argc, char *argv[])
{
    init();
    /* initialize GLUT, let it extract command-line
       GLUT options that you may provide
       - NOTE THE '&' BEFORE argc */
    glutInit(&argc, argv);

    /* specify the display to be single
       buffered and color as RGBA values */
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);


    glutInitWindowPosition(POSWX, POSWY);

    /* set the initial window size */
    glutInitWindowSize(WIDTH, HEIGHT);

    /* create the window and store the handle to it */
    glutCreateWindow("Experiment with drawing a square with translate and rotate movements");

    /* --- register callbacks with GLUT --- */

    glutDisplayFunc(draw);
    glutKeyboardFunc(on_key_press);
    glutMouseFunc(on_mouse_ev);
    glutReshapeFunc(on_resize);

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    /* start the GLUT main loop */
    glutMainLoop();


    exit(0);
}


void init() {
    sq.pt[0].x =  10.0f;
    sq.pt[0].y =  10.0f;

    sq.pt[1].x =  10.0f;
    sq.pt[1].y =  20.0f;

    sq.pt[2].x =  20.0f;
    sq.pt[2].y =  20.0f;

    sq.pt[3].x =  20.0f;
    sq.pt[3].y =  10.0f;
}

void draw() {

    glClear(GL_COLOR_BUFFER_BIT);

    display_square();
    display_axis();

    glFlush();
}

void display_square()
{
    /* clear the screen to white */
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0f, 0.4f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(sq.pt[0].x - 5.0f, sq.pt[0].y - 5.0f);
    glVertex2f(sq.pt[1].x - 5.0f, sq.pt[1].y - 5.0f);
    glVertex2f(sq.pt[2].x - 5.0f, sq.pt[2].y - 5.0f);
    glVertex2f(sq.pt[3].x - 5.0f, sq.pt[3].y - 5.0f);
    glEnd();
}

void apply_size()
{
    sq.pt[0].x +=  0.0f;
    sq.pt[0].y +=  0.0f;

    sq.pt[1].x +=  0.0f;
    sq.pt[1].y +=  10.0f;

    sq.pt[2].x +=  10.0f;
    sq.pt[2].y +=  10.0f;

    sq.pt[3].x +=  10.0f;
    sq.pt[3].y +=  0.0f;
}

void display_axis()
{
    // Desenha a linha vertical
    glColor3f(0.2f, 0.2f, 0.2f);
    glBegin(GL_LINES);
    glVertex2f(0.0f, MENORY);
    glVertex2f(0.0f, MAIORY);
    glEnd();

    // Desenha a linha horizontal
    glColor3f(0.2f, 0.2f, 0.2f);
    glBegin(GL_LINES);
    glVertex2f(MENORX, 0.0f);
    glVertex2f(MAIORX, 0.0f);
    glEnd();

}

void on_key_press(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 'q':
        case 27: /* ESC */
            exit(0);
        default:
            break;
    }
}

void on_mouse_ev(int bt, int state, int x, int y)
{

    printf("Clicked at X: %d and Y: %d\n\n", x, y);
    x = x/4 - 50;
    y = (y/4-50) * (-1);
    printf("Adapting to axis extremes X: %d and Y: %d\n\n", x, y);

    if (bt == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        for (int i = 0; i < 4; i++) {
            translate(&sq.pt[i], x, y);
        }
        apply_size();
    } else if (GLUT_RIGHT_BUTTON) {
        for (int i = 0; i < 4; i++) {
            rotate(&sq.pt[i], x, y, ANGLE);
        }
    }

    glutPostRedisplay();
}

void calc(GLfloat m[][4], struct Point *origin) {
    GLfloat Pt[4];
    Pt[0] = origin->x; Pt[1] = origin->y; Pt[2] = 1.0; Pt[3] = 1.0;
    origin->x = 0; origin->y = 0; origin->z = 0;

    for (int i = 0; i < 4; i++)
    {
        origin->x = origin->x + m[0][i] * Pt[i];
        origin->y = origin->y + m[1][i] * Pt[i];
        origin->z = origin->z + m[2][i] * Pt[i];
    }
}


void rotate(struct Point *origin, GLfloat x, GLfloat y, GLfloat angle)
{
    GLfloat dX1 = 0 - x;
    GLfloat dY1 = 0 - y;

    GLfloat m_translate[4][4] = { { 1.0, 0.0, 0.0, dX1 },
                                  { 0.0, 1.0, 0.0, dY1  },
                                  { 0.0, 0.0, 1.0, 0.0 },
                                  { 0.0, 0.0, 0.0, 1.0 }
    };
    origin->x -= 5;
    origin->y -= 5;
    //calc(m_translate, origin);

    GLfloat m_rotate[4][4] = { { (GLfloat) cos(angle * PI / 180.0), (GLfloat) -sin(angle * PI / 180.0), 0.0, 0.0 },
                        { (GLfloat) sin(angle * PI / 180.0), (GLfloat) cos(angle * PI / 180.0),  0.0, 0.0 },
                        { 0.0, 0.0,	1.0, 0.0 },
                        { 0.0, 0.0, 0.0, 1.0 }
    };

    //calc(m_rotate, origin);

    GLfloat dX2 = dX1 *(-1);
    GLfloat dY2 = dY1 *(-1);

    GLfloat m_translate2[4][4] = { { 1.0, 0.0, 0.0, dX2 },
                                  { 0.0, 1.0, 0.0, dY2 },
                                  { 0.0, 0.0, 1.0, 0.0 },
                                  { 0.0, 0.0, 0.0, 1.0 }
    };


    GLfloat acc1[4][4];
    GLfloat acc2[4][4];
    multiply(m_rotate, m_translate, acc1);
    multiply(m_translate2, acc1, acc2);


    calc(acc2, origin);
    origin->x += 5;
    origin->y += 5;

}

void translate(struct Point *origin, GLfloat x, GLfloat y)
{
    GLfloat dX = x - origin->x;
    GLfloat dY = y - origin->y;
    printf("Calculated deltas X: %f Y:%f\n\n", dX, dY);

    GLfloat m_translate[4][4] = { { 1.0, 0.0, 0.0, dX },
                                  { 0.0, 1.0, 0.0, dY },
                                  { 0.0, 0.0, 1.0, 0.0 },
                                  { 0.0, 0.0, 0.0, 1.0 }
    };

    calc(m_translate, origin);
}

void on_resize(GLsizei w, GLsizei h)
{
    GLfloat largura, altura;

    if (h == 0) h = 1;

    largura = w;
    altura = h;

    glViewport(0, 0, largura, altura);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if (largura <= altura)
        gluOrtho2D(MENORX, MAIORX, MENORY*altura / largura, MAIORY*altura / largura);
    else
        gluOrtho2D(MENORX*largura / altura, MAIORX*largura / altura, MENORY, MAIORY);
}

void multiply(GLfloat A[][4], GLfloat B[][4], GLfloat M[][4])
{

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            M[i][j] = 0;
            for (int k = 0; k < 4; k++)
            {
                M[i][j] = M[i][j] + A[i][k] * B[k][j];
            }
        }
    }
}
