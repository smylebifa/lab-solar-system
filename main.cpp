#include "main.h"

const int FPS = 30;
const int COUNT_TIMER = 1000 / FPS;
const double G = pow(6.6738480808080, -11);

bool keys[256];
int width, height;
double XScreen, YScreen, Xf, Yf;
Body Planet[4];

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

    //t2->Speed.x += x * a2;
    //t2->Speed.y += y * a2;

    t1->Move();
    //t2->Move();
}

void Reshape(int width, int height)
{
    /* Высота 1.0  - это 768 пиксилей, если высота монитора больше, 
    следовательно вещественное значение больше. Такая же ситуация с шириной. 
    Сделано для того, чтобы разрешение экрана давало приимущество*/
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

void MouseDown(int button, int state, int x, int y)
{
    Xf = XScreen * 2 * (float)x / (float)width - (XScreen);
    Yf = -(YScreen * 2 * (float)y / (float)height - (YScreen));

    if (state == GLUT_DOWN)
    {
        Planet[1].Speed.x += (Xf - Planet[1].Pos.x) / 200.0;
        Planet[1].Speed.y += (Yf - Planet[1].Pos.y) / 200.0;
    }
}

void KeyProc(unsigned char key, int x, int y)
{
    if (key == 27)
        exit(0);
    keys[key] = true;
}

void KeyUpProc(unsigned char key, int x, int y)
{
    keys[key] = false;
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
    glVertex2f(Planet[0].Pos.x, Planet[0].Pos.y);
    glEnd();

    glPointSize(20);
    glBegin(GL_POINTS);
    glVertex2f(Planet[1].Pos.x, Planet[1].Pos.y);
    glEnd();

    glPointSize(19);
    glBegin(GL_POINTS);
    glVertex2f(Planet[2].Pos.x, Planet[2].Pos.y);
    glEnd();


    glPointSize(15);
    glBegin(GL_POINTS);
    glVertex2f(Planet[3].Pos.x, Planet[3].Pos.y);
    glEnd();

    //Planet[1].PaintPhysic();

    glPopMatrix();
    glutSwapBuffers();
}

void PaintTimer(int value)
{
    SpeedBody(&Planet[1], &Planet[0]);
    SpeedBody(&Planet[2], &Planet[0]);
    SpeedBody(&Planet[3], &Planet[0]);
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
    Planet[0].Pos.x = 0.0; 
    Planet[0].Pos.y = 0.0;
    Planet[0].m = 2000;
    //Planet[0].m = 2000000;
    Planet[0].Speed.x = 0;
    Planet[0].Speed.y = 0;

    // Earth    
    Planet[1].Pos.x = 0.4; 
    Planet[1].Pos.y = 0.0;
    Planet[1].m = 6;
    Planet[1].Speed.x = 0.001;
    Planet[1].Speed.y = 0.0015;

    /// Venus
    Planet[2].Pos.x = 0.3;
    Planet[2].Pos.y = 0.0;
    Planet[2].m = 5;
    Planet[2].Speed.x = 0.001;
    Planet[2].Speed.y = 0.002;

    //Mars
    Planet[3].Pos.x = 0.5;
    Planet[3].Pos.y = -0.2;
    Planet[3].m = 4;
    Planet[3].Speed.x = 0.001;
    Planet[3].Speed.y = 0.0017;

    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    char str[17] = { 0 };
    sprintf_s(str, "%dx%d:32@60", width, height);
    glutGameModeString(str);
    glutEnterGameMode();

    glutReshapeFunc(Reshape);
    glutDisplayFunc(Draw);
    glutKeyboardFunc(KeyProc);
    glutKeyboardUpFunc(KeyUpProc);
    glutDisplayFunc(Draw);
    glutPassiveMotionFunc(PassiveMotionFunc);
    glutMotionFunc(MotionFunc);
    glutMouseFunc(MouseDown);
    glutTimerFunc(30, PaintTimer, 0);
    glutTimerFunc(20, KeysTimer, 0);
    glutMainLoop();

    return 0;
}