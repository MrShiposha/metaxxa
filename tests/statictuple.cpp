#include "tests.h"

TEST_CASE("Correct size", "[metaxxa::StaticTuple]")
{
    static_assert(StaticTuple<>::size() == 0, "Invalid size of empty StaticTuple");
    static_assert(StaticTuple<int>::size() == 1, "Invalid size of StaticTuple with size == 1");
    static_assert(StaticTuple<double, char>::size() == 2, "Invalid size of StaticTuple with size == 2");
}

TEST_CASE("Is empty", "[metaxxa::StaticTuple]")
{
    static_assert(StaticTuple<>::is_empty(), "is_empty() must be true on empty StaticTuple");
    static_assert(!StaticTuple<int>::is_empty(), "is_empty() must be false on StaticTuple with size == 1");
    static_assert(!StaticTuple<double, char>::is_empty(), "is_empty() must be false on StaticTuple with size == 2");
}

TEST_CASE("Get i-th type", "[metaxxa::StaticTuple]")
{
    using T1 = StaticTuple<std::size_t>;
    using T2 = StaticTuple<double, float>;

    static_assert(is_same_v<T1::template Get<0>, std::size_t>, "Invalid T1::Get<0> type (must be std::size_t)");

    static_assert(is_same_v<T2::template Get<0>, double>, "Invalid T2::Get<0> type (must be double)");
    static_assert(is_same_v<T2::template Get<1>, float>, "Invalid T2::Get<1> type (must be float)");
}

TEST_CASE("Concat StaticTuple", "[metaxxa::StaticTuple]")
{
    SECTION("Concat Tuple with empty Tuple")
    {
        static_assert
        (
            is_same_v<StaticTuple<>::Concat<StaticTuple<>>, StaticTuple<>>, 
            "Invalid result of concat empty tuple and empty tuple"
        );

        static_assert
        (
            is_same_v<StaticTuple<int>::Concat<StaticTuple<>>, StaticTuple<int>>, 
            "Invalid result of concat StaticTuple<int> and empty tuple"
        );

        static_assert
        (
            is_same_v<StaticTuple<>::Concat<StaticTuple<int>>, StaticTuple<int>>, 
            "Invalid result of concat empty tuple and StaticTuple<int>"
        );

        static_assert
        (
            is_same_v<StaticTuple<double, char>::Concat<StaticTuple<>>, StaticTuple<double, char>>, 
            "Invalid result of concat StaticTuple<double, char> and empty tuple"
        );

        static_assert
        (
            is_same_v<StaticTuple<>::Concat<StaticTuple<double, char>>, StaticTuple<double, char>>, 
            "Invalid result of concat empty tuple and StaticTuple<double, char>"
        );
    }

    SECTION("Concat Tuple with size == 1")
    {
        static_assert
        (
            is_same_v<StaticTuple<int>::Concat<StaticTuple<char>>, StaticTuple<int, char>>, 
            "Invalid result of concat StaticTuple<int> and StaticTuple<char>"
        );

        static_assert
        (
            is_same_v<StaticTuple<char>::Concat<StaticTuple<int>>, StaticTuple<char, int>>, 
            "Invalid result of concat StaticTuple<char> and StaticTuple<int>"
        );

        static_assert
        (
            is_same_v<StaticTuple<double, float>::Concat<StaticTuple<char>>, StaticTuple<double, float, char>>, 
            "Invalid result of concat StaticTuple<double, float> and StaticTuple<char>"
        );

        static_assert
        (
            is_same_v<StaticTuple<char>::Concat<StaticTuple<double, float>>, StaticTuple<char, double, float>>, 
            "Invalid result of concat StaticTuple<char> and StaticTuple<double, char>"
        );
    }

    using T1 = StaticTuple<int, char>;
    using T2 = StaticTuple<double, float>;
    using T3 = StaticTuple<size_t>;
    using E = StaticTuple<>;

    using R = T1::template Concat<T2>
                ::template Concat<T3>
                ::template Concat<E>;

    static_assert(is_same_v<R, StaticTuple<int, char, double, float, size_t>>, "Invalid result of concat T1, T2, T3 and E");
}