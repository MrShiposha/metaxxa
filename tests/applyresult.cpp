#include "tests.h"

double f1(int, char);

char f2(double);

TEST_CASE("[metaxxa::ApplyResult]")
{
    static_assert(is_same_v<ApplyResult<decltype(f1), TypeList<int, char>>, double>);
    static_assert(is_same_v<ApplyResult<decltype(f2), TypeList<double>>, char>);
}