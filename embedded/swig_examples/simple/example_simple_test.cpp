// https://docs.python.org/3/extending/embedding.html#pure-embedding
//

#define PY_SSIZE_T_CLEAN
#include <Python.h>

#include <gtest/gtest.h>

PyMODINIT_FUNC PyInit_example( void );

class SimpleExampleModuleF : public ::testing::Test
{
    wchar_t *program;
public:

    SimpleExampleModuleF() : program{}
    {}

    ~SimpleExampleModuleF() override
    {}

    void SetUp() override
    {
        const char *current_name = ::testing::UnitTest::GetInstance()->current_test_info()->name();

        program = Py_DecodeLocale( current_name, NULL );
        ASSERT_TRUE( program != NULL )
            << "Fatal error: cannot decode program name";

        /* Add a built-in module, before Py_Initialize */
        ASSERT_NE(PyImport_AppendInittab( "example", PyInit_example), -1 )
            << "Error: could not extend in-built modules table";

        /* Pass argv[0] to the Python interpreter */
        Py_SetProgramName( program );

        /* Initialize the Python interpreter.  Required.
           If this step fails, it will be a fatal error. */
        Py_Initialize();

#if 0
        /* Optionally import the module; alternatively,
           import can be deferred until the embedded script
           imports it. */
        PyObject *pmodule = PyImport_ImportModule( "example" );
        ASSERT_TRUE( pmodule != 0 )
            // PyErr_Print();
            << "Error: could not import module 'example'\n";
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
        }
    }
}

TEST_F( SimpleExampleModuleF, t1 )
{
    {
        int rc;
        rc = PyRun_SimpleString("import sys");
        ASSERT_EQ(rc, 0);
        rc = PyRun_SimpleString("sys.path.append(\".\")");
        ASSERT_EQ(rc, 0);

        rc = PyRun_SimpleString("import example");
        ASSERT_EQ(rc, 0);
        rc = PyRun_SimpleString("print(dir(example))");
        ASSERT_EQ(rc, 0);
    }

    {
        FILE* fd = fopen("runme.py", "rb");
        if (fd == 0)
            fd = fopen("../runme.py", "rb");
        ASSERT_TRUE(fd != NULL);

        int rc;
        rc = PyRun_SimpleString("import sys");
        ASSERT_EQ(rc, 0);
        rc = PyRun_SimpleString("sys.path.append('.')");
        ASSERT_EQ(rc, 0);
        rc = PyRun_SimpleString("sys.path.append('..')");
        ASSERT_EQ(rc, 0);

        rc = PyRun_SimpleFile(fd, "runme.py");
        fclose(fd);

        ASSERT_EQ(rc, 0);
    }
}

#if 0
// FAIL
TEST_F( SimpleExampleModuleF, t1_1 )
{
    int rc;

    rc = PyRun_SimpleString( "import example" );
    ASSERT_EQ( rc, 0 );
}

TEST_F( SimpleExampleModuleF, t2 )
{
    // programmatic dir()
    // it's not going to work.
    // EXPECTED: "SystemError: frame does not exist"

    auto locals = PyObject_Dir( NULL );
    ASSERT_TRUE( locals ==  NULL );

    ASSERT_TRUE( PyErr_Occurred() );
    PyErr_Print();
}

TEST_F( SimpleExampleModuleF, t3 )
{
    auto pName = PyUnicode_DecodeFSDefault( "example" );
    auto pModule = PyImport_Import( pName );
    Py_DECREF( pName );

    ASSERT_TRUE( pModule != NULL );

    auto locals = PyObject_Dir( pModule );
    ASSERT_TRUE( locals != NULL );

    fprintf( stderr, "type: %s\n", locals->ob_type->tp_name ); // list
    dump_py_list( locals );
    Py_DECREF( locals );

    Py_DECREF( pModule );
}
#endif


// end of file