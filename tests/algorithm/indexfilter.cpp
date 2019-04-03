#include "../tests.h"

#include <iostream>

TEST_CASE("[metaxxa::IndexFilter]")
{
    using T = TypeList<int, char, double>;

    static_assert(is_same_v<IndexFilter<TypeList, Nil>, Nil>, "No indices failed (on Nil)");
    static_assert(is_same_v<IndexFilter<TypeList, T>, Nil>, "No indices failed (on T)");

    static_assert(is_same_v<IndexFilter<TypeList, T, 0>, TypeList<int>>, "Indices failed (0)");
    static_assert(is_same_v<IndexFilter<TypeList, T, 1>, TypeList<char>>, "Indices failed (1)");
    static_assert(is_same_v<IndexFilter<TypeList, T, 2>, TypeList<double>>, "Indices failed (2)");

    static_assert(is_same_v<IndexFilter<TypeList, T, 0, 1>, TypeList<int, char>>, "Indices failed (0 1)");
    static_assert(is_same_v<IndexFilter<TypeList, T, 1, 2>, TypeList<char, double>>, "Indices failed (1 2)");
    static_assert(is_same_v<IndexFilter<TypeList, T, 0, 2>, TypeList<int, double>>, "Indices failed (0 2)");

    static_assert(is_same_v<IndexFilter<TypeList, T, 1, 0>, TypeList<char, int>>, "Indices failed (1 0)");
    static_assert(is_same_v<IndexFilter<TypeList, T, 2, 1>, TypeList<double, char>>, "Indices failed (2 1)");
    static_assert(is_same_v<IndexFilter<TypeList, T, 2, 0>, TypeList<double, int>>, "Indices failed (2 0)");

    static_assert(is_same_v<IndexFilter<TypeList, T, 0, 1, 2>, TypeList<int, char, double>>, "Indices failed (0 1 2)");
    static_assert(is_same_v<IndexFilter<TypeList, T, 0, 2, 1>, TypeList<int, double, char>>, "Indices failed (0 2 1)");
    static_assert(is_same_v<IndexFilter<TypeList, T, 1, 0, 2>, TypeList<char, int, double>>, "Indices failed (1 0 2)");
    static_assert(is_same_v<IndexFilter<TypeList, T, 1, 2, 0>, TypeList<char, double, int>>, "Indices failed (1 2 0)");
    static_assert(is_same_v<IndexFilter<TypeList, T, 2, 0, 1>, TypeList<double, int, char>>, "Indices failed (2 0 1)");
    static_assert(is_same_v<IndexFilter<TypeList, T, 2, 1, 0>, TypeList<double, char, int>>, "Indices failed (2 1 0)");

}