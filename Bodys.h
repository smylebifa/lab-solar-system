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
    vector <Planet> elements; // ��������� ������ 
    
    double m; // ����� �������
    
    void Move();
    void PaintPhysic(); // ��������� ��������
};