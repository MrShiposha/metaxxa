#include "../tests.h"

TEST_CASE("[metaxxa::contains]")
{
    static_assert(!contains<TypeTuple<>, char>());
    static_assert(contains<TypeTuple<int>, int>());
    static_assert(!contains<TypeTuple<int>, char>());
    static_assert(contains<TypeTuple<int, char, double>, int>());
    static_assert(contains<TypeTuple<int, char, double>, char>());
    static_assert(contains<TypeTuple<int, char, double>, double>());
    static_assert(!contains<TypeTuple<int, char, double>, char *>());
}

TEST_CASE("[metaxxa::contains_all]")
{
    static_assert(!contains_all<TypeTuple<>, char>());
    static_assert(contains_all<TypeTuple<int>, int>());
    static_assert(!contains_all<TypeTuple<int>, char>());
    static_assert(contains_all<TypeTuple<int, char, double>, int>());
    static_assert(contains_all<TypeTuple<int, char, double>, char>());
    static_assert(contains_all<TypeTuple<int, char, double>, double>());
    static_assert(contains_all<TypeTuple<int, char, double>, int, char, double>());
    static_assert(contains_all<TypeTuple<int, char, double>, char, double>());
    static_assert(contains_all<TypeTuple<int, char, double>, char, char>());
    static_assert(!contains_all<TypeTuple<int, char, double>, char *, double>());
}