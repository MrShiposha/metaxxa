#include "tests.h"

int f1(int, int);

double f2(double, char, int);

void f3();

int f4(char);

TEST_CASE("[metaxxa::is_applicable()]")
{
    static_assert(is_applicable<decltype(f1), TypeList<int, int>>());
    static_assert(is_applicable<decltype(f2), TypeList<double, char, int>>());
    static_assert(is_applicable<decltype(f3), TypeList<>>());
    static_assert(is_applicable<decltype(f4), TypeList<char>>());

    static_assert(!is_applicable<decltype(f4), TypeList<char, char>>());
}