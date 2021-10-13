#include "main.h"

void Body::Move()
{
    Pos.x += Speed.x;
    Pos.y += Speed.y;

    if (elements.size() < 5000) 
    {
        elements.push_back(Pos);
    }
}

void Body::PaintPhysic()
{
    glColor3f(0, 1, 1);
    glPointSize(1);
    glBegin(GL_POINTS);
        
    for (auto point : elements) 
    {
        glVertex2f(point.x, point.y);
    }

    glEnd();
}