/* File : example.i */
%module example

%{
#include "example.h"
%}

%feature("autodoc", "1");

%include stl.i
/* instantiate the required template specializations */
namespace std {
    %template(IntVector)    vector<int>;
    %template(DoubleVector) vector<double>;
    %template(PointVector) vector<point_t>;
}

%extend point_t {
    char* __str__() {
        static char tmp[80];
        sprintf(tmp, "point_t(%g, %g)", $self->x, $self->y);
        return tmp;
    }

    char* __repr__() {
        static char tmp[80];
        sprintf(tmp, "example.point_t(%g, %g)", $self->x, $self->y);
        return tmp;
    }

    point_t() {
        point_t* pp = new point_t{};
        return pp;
    }

    point_t(double x, double y) {
        point_t* pp = new point_t{x, y};
        return pp;
    }
}

%extend std::vector<point_t> {
    char* __str__() {
        static char tmp[80];
        sprintf(tmp, "std::vector<point_t>(...)");
        return tmp;
    }
}

%include "carrays.i"

%array_class(point_t, point_array);

%{

//point_t* to_point_t(PyObject *in)
//{
//    void *arg1;
//    auto res1 = SWIG_ConvertPtr(in, &arg1, SWIGTYPE_p_point_array, 0 | 0);
//    if (!SWIG_IsOK(res1)) {
//        PyErr_SetString(PyExc_ValueError, "argument should be of point_array type");
//        return 0;
//    }
//
//    auto pp = (point_array *)arg1;
//    return pp->cast();
//}

%}

//%typemap(in) (point_t* data, size_t size) {
//    point_t* tmp = to_point_t($input);
//    if (!tmp)
//        return NULL;
//    $1 = tmp;
//    $2 = 10;
//};
//
//%apply(point_t* data, size_t size) { (point_t * data2, size_t size2) };

/* Let's just grab the original header file here */
%include "example.h"
