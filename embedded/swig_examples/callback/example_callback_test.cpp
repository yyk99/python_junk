//
//
//

#define PY_SSIZE_T_CLEAN
#include <Python.h>

#include <gtest/gtest.h>

#if NO_SWIG_PROXY
#   define PY_INIT PyInit_example
#   define MODULE_NAME "example"
#else
#   define PY_INIT PyInit__example
#   define MODULE_NAME "_example"
#endif

PyMODINIT_FUNC PY_INIT(void);

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

        /* Add a built-in module, before Py_Initialize */
        ASSERT_NE(PyImport_AppendInittab(MODULE_NAME, PY_INIT), -1 )
            << "Error: could not extend in-built modules table";

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
        int rc;
        rc = PyRun_SimpleString("import sys");
        ASSERT_EQ(rc, 0);
        rc = PyRun_SimpleString("sys.path.append(\".\")");
        ASSERT_EQ(rc, 0);

        rc = PyRun_SimpleString("import " MODULE_NAME);
        ASSERT_EQ(rc, 0);
        rc = PyRun_SimpleString("print(dir(" MODULE_NAME "))");
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
