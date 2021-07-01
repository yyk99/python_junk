/* File : example.i */
%module example

%feature("autodoc", "1");

%{
#include "example.h"
%}

%include typemaps.i

/*
%typemap(in) void * {
    $1 = PyLong_AsVoidPtr($input);
}

%typemap(out) void * {
    $result = PyLong_FromVoidPtr($1);
}
*/

%typemap(in) layer_handle_t {
    $1 = PyLong_AsVoidPtr($input);
}

%typemap(out) layer_handle_t {
    $result = PyLong_FromVoidPtr($1);
}

%apply(size_t* OUTPUT) { (size_t * listSize) };
// %apply(void *) { layer_handle_t }


%include carrays.i
%array_class(layer_handle_t, layer_handle_array);

%include "example.h"
