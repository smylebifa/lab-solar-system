#include "main.h"

void Body::Move()
{
    Pos.x += Speed.x;
    Pos.y += Speed.y;

    if (elements.size() < 5000) 
        elements.push_back(Pos);
}

void Body::PaintPhysic()
{
    
    /*glBegin(GL_LINE_STRIP);
    glColor3f(1.0, 1.0, 1.0);
    glVertex2f(0.2, 0.2);
    glEnd();*/

    //glVertex2i(0.5, 0.5);
    
    glColor3f(0, 1, 1);
    glPointSize(1);
    glBegin(GL_POINTS);
        
    Point point;

    for (int i = 0; i < elements.size(); i++) 
    {
        point = elements[i];
        glVertex2f(point.x, point.y);
    }

    //glVertex2f(Pos.x, Pos.y);
    //glVertex2f(Xf, Yf);
    glEnd();
}