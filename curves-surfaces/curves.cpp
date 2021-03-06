#include "curves.h"
#include <math.h>
#include <iostream>


GLfloat Bezier::gtX = 400.0f;
GLfloat Bezier::gtY = 400.0f;
GLfloat Bezier::ltX = 0.0f;
GLfloat Bezier::ltY = 0.0f;

GLfloat Hermite::tang1X = 1000.0f;
GLfloat Hermite::tang1Y = 0.0f;
GLfloat Hermite::tang2X = -1000.0f;
GLfloat Hermite::tang2Y = 0.0f;

GLfloat Parabola::gtX = 200.0f;
GLfloat Parabola::ltX = -200.0f;
GLfloat Parabola::gtY = 200.0f;
GLfloat Parabola::ltY = -200.0f;

void Bezier::draw(struct CurvePoints* cp) {

    GLfloat B[4][4] = { { -1.0f, 3.0f, -3.0f, 1.0f },
                        { 3.0f, -6.0f, 3.0f, 0.0f },
                        { -3.0f, 3.0f, 0.0f, 0.0f },
                        { 1.0f, 0.0f, 0.0f, 0.0f }
    };

    // se o numero de pontos fornecidos for zero
    // GET_POINTSD = Status de atribui��o de pontos pelo mouse
    if ((total_points == 0) && (get_points))
    {
        matrix[0][0] = cp->x; // coordenada x do primeiro ponto
        matrix[0][1] = cp->y; // ordenada y do primeiro ponto
        total_points += 1;
    }

    // se o total de pontos ainda for menor do que 4 e maior do que zero
    if ((total_points > 0) && (get_points) && (total_points < 4))
    {
        // testa se o ponto aqul clicado � diferente do anterior
        if ((matrix[total_points-1][0] != cp->x) && (matrix[total_points-1][1] != cp->y))
        {
            matrix[total_points][0] = cp->x;
            matrix[total_points][1] = cp->y;
            total_points += 1;
            if (total_points > 4) total_points = 4;
        }
    }



    // exibe os 4  pontos de controle
    glColor3f(1.0, 0.0f, 0.0f);
    glPointSize(5.0f);
    //printf("\n\n");
    for (int i = 0; i < total_points; i++)
    {
        //printf("\n%f %f", B[i][0], B[i][1]);
        glBegin(GL_POINTS);
        glVertex2f(matrix[i][0], matrix[i][1]);
        glEnd();
    }



    if (total_points == 4)
    {
        GLfloat T[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
        float pace = 0.01;

        GLfloat Mx[4];
        Mx[0] = matrix[0][0];
        Mx[1] = matrix[1][0];
        Mx[2] = matrix[2][0];
        Mx[3] = matrix[3][0];
        GLfloat xinitial = multiply(T, B, Mx);

        GLfloat My[4];
        My[0] = matrix[0][1];
        My[1] = matrix[1][1];
        My[2] = matrix[2][1];
        My[3] = matrix[3][1];
        GLfloat yinitial = multiply(T, B, My);
        GLfloat xfinal, yfinal;

        for (float i = pace; i <= 1; i += pace) {
            T[0] = (GLfloat) pow(i, 3);
            T[1] = (GLfloat) pow(i, 2);
            T[2] = (GLfloat) i;

            xfinal = multiply(T, B, Mx);
            yfinal = multiply(T, B, My);

            glBegin(GL_LINE_STRIP);
            glVertex2f(xinitial, yinitial);
            glVertex2f(xfinal, yfinal);
            glEnd();

            yinitial = yfinal;
            xinitial = xfinal;
        }
    }

}

void Hermite::draw(struct CurvePoints* cp) {
    // Matriz de Hermite de Grau 3
    GLfloat H[4][4] = { { 2.0f, -2.0f,  1.0f,  1.0f },
                        { -3.0f,  3.0f, -2.0f, -1.0f },
                        { 0.0f,  0.0f,  1.0f,  0.0f },
                        { 1.0f,  0.0f,  0.0f,  0.0f } };

    // se o numero de pontos fornecidos for zero
    if ((total_points == 0) && (get_points))
    {
        matrix[0][0] = cp->x;  // guarda coordenada x
        matrix[0][1] = cp->y;  // guarda coordenada y
        matrix[0][2] = Hermite::tang1X;  // tangente x do angulo de incid�ncia de entrada
        matrix[0][3] = Hermite::tang1Y;  // tangente y do angulo de incid�ncia de entrada
        total_points += 1;
    }

    // se o total de pontos ainda for menor do que 4 e maior do que zero
    if ((total_points > 0) && (get_points) && (total_points < 2))
    {
        // testa se o ponto aqul clicado � diferente do anterior
        if ((matrix[total_points - 1][0] != cp->x) && (matrix[total_points - 1][1] != cp->y))
        {
            matrix[total_points][0] = cp->x; // guarda coordenada de netrada x
            matrix[total_points][1] = cp->y;  // guarda coordenada de entrada y
            matrix[total_points][2] = Hermite::tang2X;  // tangente x do a�ngulo de incid�ncia de sa�da
            matrix[total_points][3] = Hermite::tang2Y;  // tangente y do �ngulo de inci�ncia de sa�da
            total_points += 1;
            if (total_points > 2) total_points = 2;
        }
    }

    // exibe os 2  pontos de controle
    glColor3f(1.0, 0.0f, 0.0f);
    glPointSize(5.0f);
    for (int i = 0; i < total_points; i++)
    {
        printf("\n%f %f", matrix[i][0], matrix[i][1]);
        glBegin(GL_POINTS);
        glVertex2f(matrix[i][0], matrix[i][1]);
        glEnd();
    }



    if (total_points == 2)
    {

        GLfloat T[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
        float pace = 0.01;

        GLfloat Mx[4];
        Mx[0] = matrix[0][0];
        Mx[1] = matrix[1][0];
        Mx[2] = matrix[0][2];
        Mx[3] = matrix[1][2];
        GLfloat xinitial = multiply(T, H, Mx);

        GLfloat My[4];
        My[0] = matrix[0][1];
        My[1] = matrix[1][1];
        My[2] = matrix[0][3];
        My[3] = matrix[1][3];
        GLfloat yinitial = multiply(T, H, My);
        GLfloat xfinal;
        GLfloat yfinal;

        // t^3 + tˆ2 + t + 1
        for (float i = pace; i <= 1; i += pace) {
            T[0] = (GLfloat) pow(i, 3);
            T[1] = (GLfloat) pow(i, 2);
            T[2] = (GLfloat) i;

            xfinal = multiply(T, H, Mx);
            yfinal = multiply(T, H, My);

            glBegin(GL_LINE_STRIP);
            glVertex2f(xinitial, yinitial);
            glVertex2f(xfinal, yfinal);
            glEnd();

            yinitial = yfinal;
            xinitial = xfinal;
        }
        // calcule aqui sua curva de hermite
    }
}

GLfloat Hermite::multiply(GLfloat T[], GLfloat H[][4], GLfloat M[])
{
    GLfloat HM[4];

    // multiplica primeiro H por M
    for (int i = 0; i < 4; i++)
    {
    HM[i] = 0;
        for (int j = 0; j < 4; j++)
        {
            HM[i] = HM[i] + H[i][j] * M[j];
        }
    }

    // multiplica T * HM
    GLfloat R = 0;
    for (int i = 0; i < 4; i++)
    {
        R = R + T[i] * HM[i];
    }

    return R;
}

GLfloat Bezier::multiply(GLfloat T[], GLfloat H[][4], GLfloat M[])
{
    GLfloat HM[4];

    // multiplica primeiro H por M
    for (int i = 0; i < 4; i++)
    {
        HM[i] = 0;
        for (int j = 0; j < 4; j++)
        {
            HM[i] = HM[i] + H[i][j] * M[j];
        }
    }

    // multiplica T * HM
    GLfloat R = 0;
    for (int i = 0; i < 4; i++)
    {
        R = R + T[i] * HM[i];
    }

    return R;
}




void Parabola::draw() {
    // y = ax^2 + bx + c
    const GLint DIMX = (-1) * Parabola::ltX + Parabola::gtX + 1;
    const GLint DIMY = (-1) * Parabola::ltY + Parabola::gtY + 1;

    // par�metros
    GLfloat xini, yini, xend, yend;
    GLfloat x = -50, y;

    glColor3f(1.0, 0.0f, 0.0f);

    y = a * pow(x, degree) + b * x + c;
    xini = x;
    yini = y;
    // plota o promeiro ponto
    glBegin(GL_POINTS);
    glVertex2f(xini, yini);
    glEnd();

    // plota os demais pontos
    for (x = -50 + pace; x < 50; x = x + pace)
    {
        y = a * pow(x, 2) + b * x + c;
        xend = x;
        yend = y;
        glBegin(GL_LINE_STRIP);
        glVertex2f(xini, yini);
        glVertex2f(xend, yend);
        glEnd();
        xini = xend;
        yini = yend;
    }

}