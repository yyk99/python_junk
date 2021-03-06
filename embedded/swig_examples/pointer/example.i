/* File : example.i */
%module example

%feature( "autodoc", "1" );

%{
extern void add(int *, int *, int *);
extern void sub(int *, int *, int *);
extern int divide(int, int, int *);
extern int count_doubles(double *str, int len, double x);
int count_chars(char* str, int len, char c);

#include "example.h"
%}

/* This example illustrates a couple of different techniques
   for manipulating C pointers */

/* First we'll use the pointer library */
extern void add(int *x, int *y, int *result);
%include cpointer.i
%pointer_functions(int, intp);

/* Next we'll use some typemaps */

%include typemaps.i
extern void sub(int *INPUT, int *INPUT, int *OUTPUT);

/* Next we'll use typemaps and the %apply directive */

%apply int *OUTPUT { int *r };
extern int divide(int n, int d, int *r);

/* more examples - C arrays */

%{
void foo(double x[10]);
void bar(double a[4], double b[8]);
double summer(double *data, int size);
int parity(char *data, int size, int initial);

void get_key( int key, char *BUFFER );

char *gen_key();
%}


%{
static int convert_darray(PyObject *input, double *ptr, int size) {
  int i;
  if (!PySequence_Check(input)) {
      PyErr_SetString(PyExc_TypeError,"Expecting a sequence");
      return 0;
  }
  if (PyObject_Length(input) != size) {
      PyErr_SetString(PyExc_ValueError,"Sequence size mismatch");
      return 0;
  }
  for (i =0; i < size; i++) {
      PyObject *o = PySequence_GetItem(input,i);
      if (!PyFloat_Check(o)) {
         Py_XDECREF(o);
         PyErr_SetString(PyExc_ValueError,"Expecting a sequence of floats");
         return 0;
      }
      ptr[i] = PyFloat_AsDouble(o);
      Py_DECREF(o);
  }
  return 1;
}

static double *
to_double_vector(PyObject *input, int *size)
{
    if (!PySequence_Check(input)) {
        PyErr_SetString(PyExc_TypeError, "Expecting a sequence");
        return NULL;
    }

    *size = (int)PyObject_Length(input);
    double* ptr = (double*)malloc(*size * sizeof(double));
    if (!ptr) {
        PyErr_SetString(PyExc_ValueError, "Cannot allocate data vector");
        return NULL;
    }

    for (int i = 0; i < *size; ++i)
    {
        PyObject* o = PySequence_GetItem(input, i);
        if (!PyFloat_Check(o)) {
            Py_XDECREF(o);
            PyErr_SetString(PyExc_ValueError, "Expecting a sequence of floats");
            return NULL;
        }
        ptr[i] = PyFloat_AsDouble(o);
        Py_DECREF(o);
    }

    return ptr;
}
%}

%{
void print_error_if()
{
    if (PyErr_Occurred())
        PyErr_Print();
}

static Point*
to_Point_vector(PyObject *input, size_t *size)
{
    if ( !PySequence_Check( input ) ) {
        PyErr_SetString( PyExc_TypeError, "Expecting a sequence" );
        return NULL;
    }

    *size = (int) PyObject_Length( input );
    Point *ptr = (Point *) malloc( *size * sizeof(Point));
    if ( !ptr ) {
        PyErr_SetString( PyExc_ValueError, "Cannot allocate data vector" );
        return NULL;
    }

    for ( int i = 0; i < *size; ++i )
    {
        PyObject *o = PySequence_GetItem( input, i );
        //if ( o->) {
        //    Py_XDECREF( o );
        //    PyErr_SetString( PyExc_ValueError, "Expecting a sequence of floats" );
        //    return NULL;
        //}
        ptr[i].x = 0.5;
        ptr[i].y = 1.5;
        Py_DECREF( o );
    }

    return ptr;
}
%}

%typemap(in) double [ANY](double temp[$1_dim0]) {
   if (!convert_darray($input,temp,$1_dim0)) {
      return NULL;
   }
   $1 = &temp[0];
}

%include "cdata.i"
%include "cstring.i"
//%cdata (double)

%typemap(in) (double *data, int size) {
  double *tmp = to_double_vector($input, & $2);
  if(!tmp)
    return NULL;
  $1 = tmp;
}

%typemap(in) (char* str, int len) {
    $1 = PyString_AsString($input);   /* char *str */
    $2 = (int)PyString_Size($input);       /* int len   */
}

int count_chars(char* str, int len, char c);
int count_doubles(double *str, int len, double x);

extern void foo(double x[10]);
extern void bar(double a[4], double b[8]);
double summer(double *data, int size);

%apply (char *STRING, int LENGTH) { (char *data, int size) };
// ...
int parity(char *data, int size, int initial);


/* Set the input argument to point to a temporary variable */
%typemap(in, numinputs = 0) Point *out %{
    $1 = malloc(sizeof(Point));
%}

%typemap(argout) Point *out {
    // Append output value $1 to $result
    {
        %append_output(SWIG_NewPointerObj($1,$1_descriptor,1));
    }
}

%typemap(in) (Point const *d1, size_t s1) {
    Point* tmp = to_Point_vector($input, & $2);
    if (!tmp)
        return NULL;
    $1 = tmp;
}


// Another case of Point *
%include carrays.i
%array_class( Point, Point_array );

// char *BUFFER32
%typemap( in, numinputs = 0 ) char *BUFFER32 () %{
    $1 = (char *) malloc( 32 );
%}

%typemap( argout ) char *BUFFER32 {
    PyObject *tmp = $result;
    long len = 0;
    int res = SWIG_AsVal_long( tmp, &len );
    if ( !SWIG_IsOK( res ) ) {
        free( $1 );
        SWIG_fail;
    }
    $result = SWIG_From_CharPtrAndSize( $1, len );
    Py_DECREF( tmp ); //probably?
    free( $1 );
}

void get_key( int key, char *BUFFER );

char *gen_key();

%include "example.h"
