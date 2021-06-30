/* File : example.i */
%module example

%feature("autodoc", "1");

%{
#include "example.h"
%}

%include typemaps.i

/* 
%typemap(in) int{
    $1 = PyInt_AsLong($input);
}

%typemap(out) int{
    $result = PyInt_FromLong($1);
}
Convert from Python-- > C 
*/

%include carrays.i
%array_class(layer_handle_t, layer_handle_array);

%apply(size_t* OUTPUT) { (size_t * listSize) };

%include "example.h"
