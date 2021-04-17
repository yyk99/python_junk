/* File : example.c */

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