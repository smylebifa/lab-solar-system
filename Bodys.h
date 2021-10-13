#include "vector"

using namespace std;

struct Planet
{
    double x, y;
};

class Body
{
public:
    Planet Pos, Speed;
    vector <Planet> elements; // положение планет 
    
    double m; // масса планеты
    
    void Move();
    void PaintPhysic(); // отрисовка векторов
};