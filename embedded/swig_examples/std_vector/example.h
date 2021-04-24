/* File : example.h */

#include <vector>
#include <algorithm>
#include <functional>
#include <numeric>

double average(std::vector<int> v) {
    return std::accumulate(v.begin(),v.end(),0.0)/v.size();
}

std::vector<double> half(const std::vector<double>& v) {
    std::vector<double> w(v);
    for (unsigned int i=0; i<w.size(); i++)
        w[i] /= 2.0;
    return w;
}

void halve_in_place(std::vector<double>& v) {
    for (std::vector<double>::iterator it = v.begin(); it != v.end(); ++it)
        *it /= 2.0;
}

typedef struct {
    double x;
    double y;
} point_t;

void add_in_place(point_t *u, point_t *v, size_t size)
{
    for (int i = 0; i != size; ++i)
    {
        u[i].x += v[i].x;
        u[i].y += v[i].y;
    }
}

