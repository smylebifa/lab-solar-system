#include "main.h"
void Body::Move()
{
    Pos.x += Speed.x;
    Pos.y += Speed.y;
}

void Body::PaintPhysic()
{
    glColor3f(1, 0, 0);

    glBegin(GL_LINES);
    glVertex2f(Pos.x, Pos.y);
    glVertex2f(Pos.x + Speed.x * 20, Pos.y + Speed.y * 20);

    glColor3f(0, 1, 1);

    glVertex2f(Pos.x, Pos.y);
    glVertex2f(Xf, Yf);
    glEnd();
}