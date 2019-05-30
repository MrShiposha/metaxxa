#include "../tests.h"

#include <iostream>

TEST_CASE("[metaxxa::Unique]")
{
    static_assert(std::is_same_v<Unique<TypeTuple, TypeTuple<>>, TypeTuple<>>);
    static_assert(std::is_same_v<Unique<TypeTuple, TypeTuple<int>>, TypeTuple<int>>);
    static_assert(std::is_same_v<Unique<TypeTuple, TypeTuple<int, int, int>>, TypeTuple<int>>);
    static_assert(std::is_same_v<Unique<TypeTuple, TypeTuple<int, char, double>>, TypeTuple<int, char, double>>);
    static_assert(std::is_same_v<Unique<TypeTuple, TypeTuple<int, int, double, char, char, double>>, TypeTuple<int, double, char>>);
}

TEST_CASE("[metaxxa::IsUnique]")
{
    static_assert(std::is_same_v<IsUnique<TypeTuple<>>, std::true_type>);
    static_assert(std::is_same_v<IsUnique<TypeTuple<int>>, std::true_type>);
    static_assert(std::is_same_v<IsUnique<TypeTuple<int, int, int>>, std::false_type>);
    static_assert(std::is_same_v<IsUnique<TypeTuple<int, char, double>>, std::true_type>);
    static_assert(std::is_same_v<IsUnique<TypeTuple<int, int, double, char, char, double>>, std::false_type>);

    static_assert(is_unique<TypeTuple<>>());
    static_assert(is_unique<TypeTuple<int>>());
    static_assert(!is_unique<TypeTuple<int, int, int>>());
    static_assert(is_unique<TypeTuple<int, char, double>>());
    static_assert(!is_unique<TypeTuple<int, int, double, char, char, double>>());
}