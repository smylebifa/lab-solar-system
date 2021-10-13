#include "vector"

using namespace std;

struct Point
{
    double x, y;
};

class Body
{
public:
    Point Pos, Speed;
    vector <Point> elements; 
    
    double m; // масса
    
    void Move();
    void PaintPhysic(); // отрисовка векторов
};