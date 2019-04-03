#include "tests.h"

TEST_CASE("Correct size", "[metaxxa::TypeTuple]")
{
    static_assert(TypeTuple<>::size() == 0, "Invalid size of empty TypeTuple");
    static_assert(TypeTuple<int>::size() == 1, "Invalid size of TypeTuple with size == 1");
    static_assert(TypeTuple<double, char>::size() == 2, "Invalid size of TypeTuple with size == 2");

    static_assert(tuple_size_v<TypeTuple<>> == 0, "Invalid tuple_size_v of empty TypeTuple");
    static_assert(tuple_size_v<TypeTuple<int>> == 1, "Invalid tuple_size_v of TypeTuple with size == 1");
    static_assert(tuple_size_v<TypeTuple<double, char>> == 2, "Invalid tuple_size_v of TypeTuple with size == 2");
}

TEST_CASE("Is empty", "[metaxxa::TypeTuple]")
{
    static_assert(TypeTuple<>::is_empty(), "is_empty() must be true on empty TypeTuple");
    static_assert(!TypeTuple<int>::is_empty(), "is_empty() must be false on TypeTuple with size == 1");
    static_assert(!TypeTuple<double, char>::is_empty(), "is_empty() must be false on TypeTuple with size == 2");
}

TEST_CASE("Get i-th type", "[metaxxa::TypeTuple]")
{
    using T1 = TypeTuple<std::size_t>;
    using T2 = TypeTuple<double, float>;

    static_assert(is_same_v<T1::template Get<0>, std::size_t>, "Invalid T1::Get<0> type (must be std::size_t)");
    static_assert(is_same_v<tuple_element_t<0, T1>, std::size_t>, "Invalid tuple_element_t<0, T1> type (must be std::size_t)");

    static_assert(is_same_v<T2::template Get<0>, double>, "Invalid T2::Get<0> type (must be double)");
    static_assert(is_same_v<T2::template Get<1>, float>, "Invalid T2::Get<1> type (must be float)");

    static_assert(is_same_v<tuple_element_t<0, T2>, double>, "Invalid tuple_element_t<0, T2> type (must be double)");
    static_assert(is_same_v<tuple_element_t<1, T2>, float>, "Invalid tuple_element_t<1, T2> type (must be float)");
}

TEST_CASE("Concat TypeTuple", "[metaxxa::TypeTuple]")
{
    SECTION("Concat Tuple with empty Tuple")
    {
        static_assert
        (
            is_same_v<TypeTuple<>::Concat<TypeTuple<>>, TypeTuple<>>, 
            "Invalid result of concat empty tuple and empty tuple"
        );

        static_assert
        (
            is_same_v<TypeTuple<int>::Concat<TypeTuple<>>, TypeTuple<int>>, 
            "Invalid result of concat TypeTuple<int> and empty tuple"
        );

        static_assert
        (
            is_same_v<TypeTuple<>::Concat<TypeTuple<int>>, TypeTuple<int>>, 
            "Invalid result of concat empty tuple and TypeTuple<int>"
        );

        static_assert
        (
            is_same_v<TypeTuple<double, char>::Concat<TypeTuple<>>, TypeTuple<double, char>>, 
            "Invalid result of concat TypeTuple<double, char> and empty tuple"
        );

        static_assert
        (
            is_same_v<TypeTuple<>::Concat<TypeTuple<double, char>>, TypeTuple<double, char>>, 
            "Invalid result of concat empty tuple and TypeTuple<double, char>"
        );
    }

    SECTION("Concat Tuple with size == 1")
    {
        static_assert
        (
            is_same_v<TypeTuple<int>::Concat<TypeTuple<char>>, TypeTuple<int, char>>, 
            "Invalid result of concat TypeTuple<int> and TypeTuple<char>"
        );

        static_assert
        (
            is_same_v<TypeTuple<char>::Concat<TypeTuple<int>>, TypeTuple<char, int>>, 
            "Invalid result of concat TypeTuple<char> and TypeTuple<int>"
        );

        static_assert
        (
            is_same_v<TypeTuple<double, float>::Concat<TypeTuple<char>>, TypeTuple<double, float, char>>, 
            "Invalid result of concat TypeTuple<double, float> and TypeTuple<char>"
        );

        static_assert
        (
            is_same_v<TypeTuple<char>::Concat<TypeTuple<double, float>>, TypeTuple<char, double, float>>, 
            "Invalid result of concat TypeTuple<char> and TypeTuple<double, char>"
        );
    }

    using T1 = TypeTuple<int, char>;
    using T2 = TypeTuple<double, float>;
    using T3 = TypeTuple<size_t>;
    using E = TypeTuple<>;

    using R = T1::template Concat<T2>
                ::template Concat<T3>
                ::template Concat<E>;

    static_assert(is_same_v<R, TypeTuple<int, char, double, float, size_t>>, "Invalid result of concat T1, T2, T3 and E");
}