#include "../tests.h"

#include <iostream>

TEST_CASE("[metaxxa::IndexFilter]")
{
    using T = List<int, char, double>;

    static_assert(is_same_v<IndexFilter<List, Nil>, Nil>, "No indices failed (on Nil)");
    static_assert(is_same_v<IndexFilter<List, T>, Nil>, "No indices failed (on T)");

    static_assert(is_same_v<IndexFilter<List, T, 0>, List<int>>, "Indices failed (0)");
    static_assert(is_same_v<IndexFilter<List, T, 1>, List<char>>, "Indices failed (1)");
    static_assert(is_same_v<IndexFilter<List, T, 2>, List<double>>, "Indices failed (2)");

    static_assert(is_same_v<IndexFilter<List, T, 0, 1>, List<int, char>>, "Indices failed (0 1)");
    static_assert(is_same_v<IndexFilter<List, T, 1, 2>, List<char, double>>, "Indices failed (1 2)");
    static_assert(is_same_v<IndexFilter<List, T, 0, 2>, List<int, double>>, "Indices failed (0 2)");

    static_assert(is_same_v<IndexFilter<List, T, 1, 0>, List<char, int>>, "Indices failed (1 0)");
    static_assert(is_same_v<IndexFilter<List, T, 2, 1>, List<double, char>>, "Indices failed (2 1)");
    static_assert(is_same_v<IndexFilter<List, T, 2, 0>, List<double, int>>, "Indices failed (2 0)");

    static_assert(is_same_v<IndexFilter<List, T, 0, 1, 2>, List<int, char, double>>, "Indices failed (0 1 2)");
    static_assert(is_same_v<IndexFilter<List, T, 0, 2, 1>, List<int, double, char>>, "Indices failed (0 2 1)");
    static_assert(is_same_v<IndexFilter<List, T, 1, 0, 2>, List<char, int, double>>, "Indices failed (1 0 2)");
    static_assert(is_same_v<IndexFilter<List, T, 1, 2, 0>, List<char, double, int>>, "Indices failed (1 2 0)");
    static_assert(is_same_v<IndexFilter<List, T, 2, 0, 1>, List<double, int, char>>, "Indices failed (2 0 1)");
    static_assert(is_same_v<IndexFilter<List, T, 2, 1, 0>, List<double, char, int>>, "Indices failed (2 1 0)");

}