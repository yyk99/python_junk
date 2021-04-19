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

// we have to understand how struct object is created in the wrapper.
Point make_point2( double x, double y );

double perimeter(Point const * d1, size_t s1);

void add_points( Point const *p1, Point const *p2, Point *out );

#endif
