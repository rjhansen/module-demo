#define BOOST_TEST_MODULE example

#include <boost/test/included/unit_test.hpp>

#include "hello.h"

BOOST_AUTO_TEST_CASE( can_link )
{
    std::string test_case { "Hello, Harry Dresden!" };
    std::string actual_result { hello_world("Harry Dresden") };
    BOOST_REQUIRE_EQUAL(test_case, actual_result);
}

