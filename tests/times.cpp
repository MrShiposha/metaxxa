#include "tests.h"

TEST_CASE("[metaxxa::Times]")
{
    using T0 = TypeList<>;
    using T1 = TypeList<int>;
    using T2 = TypeList<int, int>;

    static_assert(std::is_same_v<Times<TypeList, 0, int>, T0>, "Invalid Times<TypeList, 0, int>");
    static_assert(std::is_same_v<Times<TypeList, 1, int>, T1>, "Invalid Times<TypeList, 1, int>");
    static_assert(std::is_same_v<Times<TypeList, 2, int>, T2>, "Invalid Times<TypeList, 2, int>");
}