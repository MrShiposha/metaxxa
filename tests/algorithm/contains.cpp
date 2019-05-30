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

    static_assert(std::is_same_v<Contains<TypeTuple<int, char, double>, int>, std::true_type>);
    static_assert(std::is_same_v<Contains<TypeTuple<int, char, double>, int*>, std::false_type>);
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

    static_assert(std::is_same_v<ContainsAll<TypeTuple<int, char, double>, int, double>, std::true_type>);
    static_assert(std::is_same_v<ContainsAll<TypeTuple<int, char, double>, int*, double>, std::false_type>);
}

TEST_CASE("[metaxxa::contains_packed]")
{
    static_assert(!contains_packed<TypeTuple<>, TypeTuple<char>>());
    static_assert(contains_packed<TypeTuple<int>, TypeTuple<int>>());
    static_assert(!contains_packed<TypeTuple<int>, TypeTuple<char>>());
    static_assert(contains_packed<TypeTuple<int, char, double>, TypeTuple<int>>());
    static_assert(contains_packed<TypeTuple<int, char, double>, TypeTuple<char>>());
    static_assert(contains_packed<TypeTuple<int, char, double>, TypeTuple<double>>());
    static_assert(contains_packed<TypeTuple<int, char, double>, TypeTuple<int, char, double>>());
    static_assert(contains_packed<TypeTuple<int, char, double>, TypeTuple<char, double>>());
    static_assert(contains_packed<TypeTuple<int, char, double>, TypeTuple<char, char>>());
    static_assert(!contains_packed<TypeTuple<int, char, double>, TypeTuple<char *, double>>());

    static_assert(std::is_same_v<ContainsPacked<TypeTuple<int, char, double>, TypeTuple<int, double>>, std::true_type>);
    static_assert(std::is_same_v<ContainsPacked<TypeTuple<int, char, double>, TypeTuple<int*, double>>, std::false_type>);
}