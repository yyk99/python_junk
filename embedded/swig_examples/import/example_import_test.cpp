//
//
//

#define PY_SSIZE_T_CLEAN
#include <Python.h>

#include <gtest/gtest.h>
#include <malloc.h>

PyMODINIT_FUNC PyInit__base(void);
PyMODINIT_FUNC PyInit__foo(void);
PyMODINIT_FUNC PyInit__bar(void);
PyMODINIT_FUNC PyInit__spam( void );

class SwigExampleModuleF : public ::testing::Test
{
    wchar_t *program;
public:

    SwigExampleModuleF() : program{}
    {}

    ~SwigExampleModuleF() override
    {}

    void SetUp() override
    {
        const char *current_name = ::testing::UnitTest::GetInstance()->current_test_info()->name();

        program = Py_DecodeLocale( current_name, NULL );
        ASSERT_TRUE( program != NULL )
            << "Fatal error: cannot decode program name";

        /* import sub-modules */
        ASSERT_EQ(PyImport_AppendInittab("_base", PyInit__base), 0);
        ASSERT_EQ(PyImport_AppendInittab("_foo", PyInit__foo), 0);
        ASSERT_EQ( PyImport_AppendInittab( "_bar", PyInit__bar ), 0 );
        ASSERT_EQ( PyImport_AppendInittab( "_spam", PyInit__spam ), 0 );

        /* Pass argv[0] to the Python interpreter */
        Py_SetProgramName( program );

        /* Initialize the Python interpreter.  Required.
           If this step fails, it will be a fatal error. */
        Py_Initialize();
    }

    void TearDown() override
    {
        PyMem_RawFree( program );
        int ok = Py_FinalizeEx();
        EXPECT_NE( ok, -1 );
    }
};

TEST_F(SwigExampleModuleF, runme_py)
{
    {
        std::cout << "CWD=" << getcwd( (char *)alloca( 256 ), 256 ) << std::endl;
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
