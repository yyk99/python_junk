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
%array_class(point_t, point_array);

%extend point_t{
    point_t(double x, double y)
    {
        point_t *obj = (point_t*)calloc(1, sizeof(point_t));
        obj->x = x;
        obj->y = y;

        return obj;
    }

    point_t()
    {
        point_t *obj = (point_t*)calloc(1, sizeof(point_t));

        return obj;
    }
};

%{
static PyObject* s_messageCB_t_functionCB;
void messageCB(const char* msg)
{
    if (s_messageCB_t_functionCB)
    {
        auto pArgs = PyTuple_New(1);
        auto pValue = PyString_FromString(msg);
        PyTuple_SetItem(pArgs, 0, pValue); /* pValue reference stolen here: */
        pValue = PyObject_CallObject(s_messageCB_t_functionCB, pArgs);
        Py_DECREF(pArgs);
        if (pValue == NULL) {
            Py_DECREF(s_messageCB_t_functionCB);
            s_messageCB_t_functionCB = NULL;
            PyErr_Print();
            fprintf(stderr, "Call failed\n");
        }
    }
}
%}

%typemap(in) messageCB_t functionCB {
    /* convert to callback object */
    if ($input && PyCallable_Check($input)) {
        s_messageCB_t_functionCB = $input;
        $1 = messageCB;
    }
    else {
        SWIG_Error(0x42, "Argument is not callable");
        return NULL;
    }
}

%include "example.h"
