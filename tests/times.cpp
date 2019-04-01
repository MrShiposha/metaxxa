#include "tests.h"

TEST_CASE("[metaxxa::Times]")
{
    using T0 = List<>;
    using T1 = List<int>;
    using T2 = List<int, int>;

    static_assert(std::is_same_v<Times<List, 0, int>, T0>, "Invalid Times<List, 0, int>");
    static_assert(std::is_same_v<Times<List, 1, int>, T1>, "Invalid Times<List, 1, int>");
    static_assert(std::is_same_v<Times<List, 2, int>, T2>, "Invalid Times<List, 2, int>");
}