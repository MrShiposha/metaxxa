#include "tests.h"

TEST_CASE("Is instatiation of template", "[metaxxa::is_instantiation_of]")
{
    static_assert(is_instatiation_of<TypeTuple, TypeTuple<int, char, double>>());
    static_assert(!is_instatiation_of<TypeTuple, std::tuple<int, char, double>>());
    static_assert(!is_instatiation_of<TypeTuple, int>());
}

TEST_CASE("Is instatiation of template with literal parameter", "[metaxxa::is_instantiation_of]")
{
    static_assert(is_instatiation_of<std::size_t, std::integer_sequence, std::index_sequence<1, 2, 3>>());
    static_assert(is_instatiation_of<char, LiteralList, LiteralList<char, 'a', 'b'>>());
    static_assert(!is_instatiation_of<char, LiteralList, LiteralList<int, 0, 1>>());
    static_assert(!is_instatiation_of<std::size_t, LiteralList, std::index_sequence<1, 2, 3>>());
    static_assert(!is_instatiation_of<short, LiteralList, int>());
}