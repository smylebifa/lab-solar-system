struct Point
{
    double x, y;
};

class Body
{
public:
    Point Pos, Speed;
    double m; // �����
    void Move();
    void PaintPhysic(); // ��������� ��������
};