// https://docs.python.org/3/extending/embedding.html#pure-embedding
//

#define PY_SSIZE_T_CLEAN
#include <Python.h>

#include <gtest/gtest.h>

PyMODINIT_FUNC PyInit__example( void );

class ConstantsExampleModuleF : public ::testing::Test
{
    wchar_t *program;
public:

    ConstantsExampleModuleF() : program{}
    {}

    ~ConstantsExampleModuleF() override
    {}

    void SetUp() override
    {
        const char *current_name = ::testing::UnitTest::GetInstance()->current_test_info()->name();

        program = Py_DecodeLocale( current_name, NULL );
        ASSERT_TRUE( program != NULL )
            << "Fatal error: cannot decode program name";

        /* Add a built-in module, before Py_Initialize */
        ASSERT_NE(PyImport_AppendInittab( "_example", PyInit__example), -1 )
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

TEST_F( ConstantsExampleModuleF, t1 )
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

// end of file
