#define BOOST_TEST_MODULE example
#include <boost/test/included/unit_test.hpp>
#include "hello.h"
import ModuleTest;

BOOST_AUTO_TEST_CASE( can_link )
{
    // note how we never #included the string header?  We get
    // it from hello.h, which imports the standard C++ libraries.
    // Arguably bad style for production code, but it does nicely
    // for educational purposes.
    std::string test_case { "Hello, Harry Dresden!" };

    // verifies that we can link against a module-using library
    std::string actual_result { hello_world("Harry Dresden") };

    // verifies we can use modules of our own making
    greet();

    // verifies our library gives the expected result.
    BOOST_REQUIRE_EQUAL(test_case, actual_result);
}

