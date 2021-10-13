#include "main.h"

const int FPS = 30;
const int COUNT_TIMER = 100 / FPS;
const double G = pow(6.6738480808080, -11);

bool keys[256];
int width, height;
double XScreen, YScreen, Xf, Yf;
Body Planets[5];

void SpeedBody(Body* t1, Body* t2)
{
    double x = (t2->Pos.x) - (t1->Pos.x);
    double y = (t2->Pos.y) - (t1->Pos.y);
    
    double length = sqrt(x * x + y * y);
    
    x = x / length;
    y = y / length;
    
    double a = (G * t1->m * t2->m) / (length * length);
    
    double a1 = a / t1->m;
    double a2 = a / t2->m;

    t1->Speed.x += x * a1;
    t1->Speed.y += y * a1;

    t1->Move();
}

void Reshape(int width, int height)
{
    XScreen = (double)width / (double)1280;
    YScreen = (double)height / (double)1024;

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-XScreen, XScreen, -YScreen, YScreen);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void MotionFunc(int x, int y)
{
    Xf = XScreen * 2 * (float)x / (float)width - (XScreen);
    Yf = -(YScreen * 2 * (float)y / (float)height - (YScreen));
}

void PassiveMotionFunc(int x, int y)
{
    Xf = XScreen * 2 * (float)x / (float)width - (XScreen);
    Yf = -(YScreen * 2 * (float)y / (float)height - (YScreen));
}

// Выход с помощью escape
void KeyProc(unsigned char key, int x, int y)
{
    if (key == 27)
        exit(0);
    keys[key] = true;
}


void Draw(void)
{
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();
    glColor3f(0.6, 0.6, 0.6);

    glBegin(GL_LINES);
    glVertex2f(-1.0, 0.0);
    glVertex2f(1.0, 0.0);

    glVertex2f(0.0, -1.0);
    glVertex2f(0.0, 1.0);
    glEnd();

    glColor3f(0.5, 0.5, 1);

    glPointSize(100);
    glEnable(GL_POINT_SMOOTH);

    glBegin(GL_POINTS);
    glVertex2f(Planets[0].Pos.x, Planets[0].Pos.y);
    glEnd();

    glPointSize(20);
    glBegin(GL_POINTS);
    glVertex2f(Planets[1].Pos.x, Planets[1].Pos.y);
    glEnd();

    glPointSize(19);
    glBegin(GL_POINTS);
    glVertex2f(Planets[2].Pos.x, Planets[2].Pos.y);
    glEnd();

    glPointSize(15);
    glBegin(GL_POINTS);
    glVertex2f(Planets[3].Pos.x, Planets[3].Pos.y);
    glEnd();

    glPointSize(7);
    glBegin(GL_POINTS);
    glVertex2f(Planets[4].Pos.x, Planets[4].Pos.y);
    glEnd();

    Planets[1].PaintPhysic();
    Planets[2].PaintPhysic();
    Planets[3].PaintPhysic();
    Planets[4].PaintPhysic();

    glPopMatrix();
    glutSwapBuffers();
}

void PaintTimer(int value)
{
    SpeedBody(&Planets[1], &Planets[0]);
    SpeedBody(&Planets[2], &Planets[0]);
    SpeedBody(&Planets[3], &Planets[0]);
    SpeedBody(&Planets[4], &Planets[0]);

    glutPostRedisplay();
    glutTimerFunc(COUNT_TIMER, PaintTimer, 0);
}

void KeysTimer(int value)
{
    if (keys[119] == true)
    {
    }

    if (keys[115] == true)
    {
    }

    if (keys[97] == true)
    {
    }

    if (keys[100] == true)
    {
    }

    glutTimerFunc(20, KeysTimer, 0);
}

int main(int argv, char* argc[])
{
    glutInit(&argv, argc);
    width = glutGet(GLUT_SCREEN_WIDTH);
    height = glutGet(GLUT_SCREEN_HEIGHT);

    //Sun
    Planets[0].Pos.x = 0.0; 
    Planets[0].Pos.y = 0.0;
    Planets[0].m = 2000;    
    Planets[0].Speed.x = 0;
    Planets[0].Speed.y = 0;

    // Earth    
    Planets[1].Pos.x = 0.4;
    Planets[1].Pos.y = 0.0;
    Planets[1].m = 6;
    Planets[1].Speed.x = 0.001;
    Planets[1].Speed.y = 0.0017;

    /// Venus
    Planets[2].Pos.x = 0.3;
    Planets[2].Pos.y = 0.0;
    Planets[2].m = 5;
    Planets[2].Speed.x = 0.001;
    Planets[2].Speed.y = 0.002;

    // Mars
    Planets[3].Pos.x = 0.5;
    Planets[3].Pos.y = -0.2;
    Planets[3].m = 4;
    Planets[3].Speed.x = 0.001;
    Planets[3].Speed.y = 0.0017;

    // Mercury
    Planets[4].Pos.x = 0.25;
    Planets[4].Pos.y = 0.0;
    Planets[4].m = 4;
    Planets[4].Speed.x = 0.001;
    Planets[4].Speed.y = 0.0021;

    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    char str[17] = { 0 };
    sprintf_s(str, "%dx%d:32@60", width, height);
    glutGameModeString(str);
    glutEnterGameMode();

    glutReshapeFunc(Reshape);
    glutDisplayFunc(Draw);
    glutKeyboardFunc(KeyProc);
    glutDisplayFunc(Draw);
    glutPassiveMotionFunc(PassiveMotionFunc);
    glutMotionFunc(MotionFunc);
    glutTimerFunc(30, PaintTimer, 0);
    glutTimerFunc(20, KeysTimer, 0);
    glutMainLoop();

    return 0;
}