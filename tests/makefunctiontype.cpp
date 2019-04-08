#include "tests.h"

#include <iostream>

TEST_CASE("[metaxxa::MakeFunctionType]")
{
    using T = TypeTuple<int, char, double, float>;
    using F1 = MakeFunctionType<T, 0>;
    using F2 = MakeFunctionType<T, 1>;
    using F3 = MakeFunctionType<T, 2>;
    using F4 = MakeFunctionType<T, 3>;

    static_assert(is_same_v<F1, int(char, double, float)>, "Invalid F1");
    static_assert(is_same_v<F2, char(int, double, float)>, "Invalid F2");
    static_assert(is_same_v<F3, double(int, char, float)>, "Invalid F3");
    static_assert(is_same_v<F4, float(int, char, double)>, "Invalid F4");
}