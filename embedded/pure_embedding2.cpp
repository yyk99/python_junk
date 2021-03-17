// https://docs.python.org/3/extending/embedding.html#pure-embedding
//

#define PY_SSIZE_T_CLEAN
#include <Python.h>

static int numargs = 0;

/* Return the number of arguments of the application command line */
static PyObject *
emb_numargs( PyObject *self, PyObject *args )
{
    if ( !PyArg_ParseTuple( args, ":numargs" ) )
        return NULL;
    return PyLong_FromLong( numargs );
}

static PyMethodDef EmbMethods[] = {
    {"numargs", emb_numargs, METH_VARARGS,
     "Return the number of arguments received by the process."},
    {NULL, NULL, 0, NULL}
};

static PyModuleDef EmbModule = {
    PyModuleDef_HEAD_INIT, "emb", NULL, -1, EmbMethods,
    NULL, NULL, NULL, NULL
};

static PyObject *
PyInit_emb( void )
{
    return PyModule_Create( &EmbModule );
}

int
main(int argc, char *argv[])
{
    numargs = argc;
    PyImport_AppendInittab( "emb", &PyInit_emb );

    Py_Initialize();
    PyRun_SimpleString( "import sys" );
    PyRun_SimpleString( "sys.path.append(\".\")" );

    PyRun_SimpleString( "import emb" );
    PyRun_SimpleString( "print(dir(emb))" );

    // Expected output:
    // ['__doc__', '__loader__', '__name__', '__package__', '__spec__', 'numargs']

    PyRun_SimpleString( "print('doc:', emb.__doc__)" );
    PyRun_SimpleString( "print('loader:', emb.__loader__)" );
    PyRun_SimpleString( "print('name:', emb.__name__)" );
    PyRun_SimpleString( "print('package:', emb.__package__)" );
    PyRun_SimpleString( "print('spec:', emb.__spec__)" );

    {
        // programmatic dir()
        // it's not going to work.
        // EXPECTED: "SystemError: frame does not exist"

        auto locals = PyObject_Dir( NULL );
        if ( locals ) {
            fprintf( stderr, "type: %s\n", locals->ob_type->tp_name );
            Py_DECREF( locals );
        }
        else {
            if ( PyErr_Occurred() )
                PyErr_Print();
        }
    }

    {
        // programmatic dir(emb)
        
        auto pName = PyUnicode_DecodeFSDefault( "emb" );
        auto pModule = PyImport_Import( pName );
        Py_DECREF( pName );
        if ( pModule ) {

            auto locals = PyObject_Dir( pModule );
            if ( locals ) {
                fprintf( stderr, "type: %s\n", locals->ob_type->tp_name );
                Py_DECREF( locals );
            }
            else {
                if ( PyErr_Occurred() )
                    PyErr_Print();
            }

            Py_DECREF( pModule );
        }
        else {
            if ( PyErr_Occurred() )
                PyErr_Print();
        }
    }

    if (Py_FinalizeEx() < 0) {
        return 120;
    }
    return 0;
}
// end of file