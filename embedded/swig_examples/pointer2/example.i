/* File : example.i */
%module example

%feature("autodoc", "1");

%{
#include "example.h"
%}

%include typemaps.i

%include carrays.i
%array_class(layer_handle_t, layer_handle_array);

%apply(size_t* OUTPUT) { (size_t * listSize) };

%include "example.h"
