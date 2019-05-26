#include "tests.h"
#include <iostream>
TEST_CASE("[metaxxa::is_array_of]")
{
    static_assert(!is_array_of<int, int>());
    static_assert(!is_array_of<int[1], int[42]>());
    static_assert(is_array_of<decltype("Hello"), char>());
}