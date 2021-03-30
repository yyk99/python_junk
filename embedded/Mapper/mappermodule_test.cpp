// https://docs.python.org/3/extending/embedding.html#pure-embedding
//

#define PY_SSIZE_T_CLEAN
#include <Python.h>

#include <gtest/gtest.h>

PyMODINIT_FUNC PyInit__mappermodule( void );

class MapperModuleF : public ::testing::Test
{
    wchar_t *program;
public:

    MapperModuleF() : program{}
    {}

    ~MapperModuleF() override
    {}

    void SetUp() override
    {
        const char *current_name = ::testing::UnitTest::GetInstance()->current_test_info()->name();

        program = Py_DecodeLocale( current_name, NULL );
        ASSERT_TRUE( program != NULL )
            << "Fatal error: cannot decode program name";

        /* Add a built-in module, before Py_Initialize */
        ASSERT_NE( -1, PyImport_AppendInittab( "globalmapper", PyInit__mappermodule ) )
            << "Error: could not extend in-built modules table";

        /* Pass argv[0] to the Python interpreter */
        Py_SetProgramName( program );

        /* Initialize the Python interpreter.  Required.
           If this step fails, it will be a fatal error. */
        Py_Initialize();

        PyImport_AppendInittab( "mappermodule", &PyInit__mappermodule );

#if 0
        /* Optionally import the module; alternatively,
           import can be deferred until the embedded script
           imports it. */
        PyObject *pmodule = PyImport_ImportModule( "globalmapper" );
        ASSERT_TRUE( pmodule != 0 )
            // PyErr_Print();
            << "Error: could not import module 'globalmapper'\n";
#endif
    }

    void TearDown() override
    {
        PyMem_RawFree( program );
        int ok = Py_FinalizeEx();
        EXPECT_NE( ok, -1 );
    }
};

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

TEST_F( MapperModuleF, t1 )
{
    //Py_Initialize();

    PyRun_SimpleString( "import sys" );
    PyRun_SimpleString( "sys.path.append(\".\")" );

    PyRun_SimpleString( "import mappermodule" );
    PyRun_SimpleString( "print(dir(mappermodule))" );
}


TEST_F( MapperModuleF, t2 )
{
    // programmatic dir()
    // it's not going to work.
    // EXPECTED: "SystemError: frame does not exist"

    auto locals = PyObject_Dir( NULL );
    ASSERT_TRUE( locals ==  NULL );

    ASSERT_TRUE( PyErr_Occurred() );
    PyErr_Print();
}

TEST_F( MapperModuleF, t3 )
{
    auto pName = PyUnicode_DecodeFSDefault( "mappermodule" );
    auto pModule = PyImport_Import( pName );
    Py_DECREF( pName );

    ASSERT_TRUE( pModule != NULL );

    auto locals = PyObject_Dir( pModule );
    ASSERT_TRUE( locals != NULL );

    fprintf( stderr, "type: %s\n", locals->ob_type->tp_name ); // list
    dump_py_list( locals );
    //Py_DECREF( locals );

    Py_DECREF( pModule );
}

// end of file