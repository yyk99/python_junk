/* File : example.h */

class Shape {
public:
    Shape() : x{}, y{}
    {
        nshapes++;
    }
    virtual ~Shape() 
    {
        nshapes--;
    }
    double  x, y;
    void    move(double dx, double dy);
    virtual double area() = 0;
    virtual double perimeter() = 0;
    static  int nshapes;
};

class Circle : public Shape {
private:
    double radius;
public:
    Circle(double r) : radius(r) { }
    virtual double area();
    virtual double perimeter();
};

class Square : public Shape {
private:
    double width;
public:
    Square(double w) : width(w) { }
    virtual double area();
    virtual double perimeter();
};

struct Point
{
    double x, y;
};

struct Border
{
    Point lu; // left-upper corner
    Point rb; // right-bottom corner
};

struct ShapeInfo {
    char * title;
    Border border;
};

extern "C" char* strdup(const char* s);

class ControlCenter {
public:
    ShapeInfo* getInfo(const char* id)
    {
        auto si = new ShapeInfo{ strdup(id), Border{Point{0,0}, Point{100,200}} };

        return si;
    }
};

