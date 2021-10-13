struct Point
{
    double x, y;
};

class Body
{
public:
    Point Pos, Speed;
    double m; // масса
    void Move();
    void PaintPhysic(); // Отрисовка векторов
};