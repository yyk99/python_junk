//
//
//

#ifndef POINTER_EXAMPLE_H
#define POINTER_EXAMPLE_H

typedef struct {
    double x;
    double y;
} Point;

void make_point(double x, double y, Point *out);

extern double perimeter(Point* d1, size_t s1);

#endif
