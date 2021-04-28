/* File : example.c */

#if _WIN32
#   define _CRT_SECURE_NO_WARNINGS
#endif

void add(int *x, int *y, int *result) {
  *result = *x + *y;
}

void sub(int *x, int *y, int *result) {
  *result = *x - *y;
}

int divide(int n, int d, int *r) {
   int q;
   q = n/d;
   *r = n - q*d;
   return q;
}

/* More examples */

#include <stdio.h>
#include "example.h"

void foo(double x[10])
{
    printf("foo() is here:\n");
    for (int i = 0; i < 10; ++i)
        printf("%f ", x[i]);
    printf("\n");
}

void bar(double a[4], double b[8])
{
    double s = 0;
    for (int i = 0; i < 4; ++i)
        s += a[i];
    for (int i = 0; i < 8; ++i)
        s += b[i];

    printf("bar: %f\n", s);
}

double summer(double a[], int n)
{
    double s = 0;
    for (int i = 0; i < n; ++i)
        s += a[i];

    return s;
}

int parity(char* data, int size, int initial)
{
    printf("parity(data, %d, %d)\n", size, initial);

    return 42;
}

int count_doubles(double* str, int len, double x)
{
    return 0;
}

extern void print_error_if();

int count_chars(char* str, int len, char c)
{
    print_error_if();

    if (!str)
        return -1; // ERROR
    int cnt = 0;
    while (*str)
    {
        if (*str++ == c)
            ++cnt;
    }
    return cnt;
}

void make_point(double x, double y, Point* out)
{
    out->x = x;
    out->y = y;
}



Point
make_point2(    double x, double y)
{
    Point p;
    p.x = x;
    p.y = y;

    return p;
} // end of function make_point2

#include <math.h>

double metrics( Point const *p )
{
    return sqrt( p->x * p->x + p->y * p->y );
}

double perimeter(Point const *d1, size_t s1)
{
    if(!d1)
        return 9999.0;
    double p = 0;
    for ( int i = 0; i != s1; ++i )
    {
        p += metrics( &d1[i] );
    }

    return p; // TODO:
}

void
add_points(Point const *p1, Point const *p2, Point *out)
{
    out->x = p1->x + p2->x;
    out->y = p1->x + p2->y;
} // end of function add_points

Point *
generate_points( int *outSize )
{
    static Point points[] = { {0,1}, {2,3}, {4,5} };

    *outSize = (int) (sizeof points / sizeof * points);

    return points;
}

#include <string.h>

void get_key( int key, char *BUFFER32 )
{
    (void) key;
    strcpy( BUFFER32, "Hello..." );
}

char *gen_key()
{
    return "hello...";
}