// https://docs.python.org/3/extending/embedding.html#pure-embedding
//

#define PY_SSIZE_T_CLEAN
#include <Python.h>

PyMODINIT_FUNC PyInit__mappermodule( void );

void
dump_py_list( PyObject *list )
{
    Py_ssize_t s = PyList_Size( list );
    if ( s > 0 ) {
        for ( Py_ssize_t i = 0; i < s; ++i ) {
            auto ai = PyList_GetItem( list, i );
            fprintf( stderr, "%d: %s\n", (int) i, ai->ob_type->tp_name );
            Py_ssize_t re_size;
            auto re = PyUnicode_AsWideCharString( ai, &re_size );
            if ( re ) {
                fwprintf( stderr, L"%s\n", re );
                PyMem_Free( re );
            }
            Py_DECREF( ai );
        }
    }
}

int
main(int argc, char *argv[])
{
    int numargs = argc;
    PyImport_AppendInittab( "mappermodule", &PyInit__mappermodule );

    Py_Initialize();

    PyRun_SimpleString( "import sys" );
    PyRun_SimpleString( "sys.path.append(\".\")" );

    PyRun_SimpleString( "import mappermodule" );
    PyRun_SimpleString( "print(dir(mappermodule))" );

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
        auto pName = PyUnicode_DecodeFSDefault( "mappermodule" );
        auto pModule = PyImport_Import( pName );
        Py_DECREF( pName );
        if ( pModule ) {

            auto locals = PyObject_Dir( pModule );
            if ( locals ) {
                fprintf( stderr, "type: %s\n", locals->ob_type->tp_name ); // list

                dump_py_list( locals );

                Py_DECREF( locals );
            }
            else {
                if ( PyErr_Occurred() )
                    PyErr_Print();
            }
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