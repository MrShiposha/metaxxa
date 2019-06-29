#include "../tests.h"

template <typename T>
struct Map_F0
{
    using type = typename If<std::is_arithmetic_v<T> && !std::is_same_v<T, char>>
        ::template Then<double>
        ::template Else<T>
        ::Type;
};

template <typename T, std::size_t INDEX>
struct Map_F1
{
    using type = typename If<INDEX % 2 == 0>
        ::template Then<int>
        ::template Else<char>
        ::Type;
};


template <typename T, std::size_t INDEX, typename TupleT, bool AT_BORDER = (INDEX + 1 == std::tuple_size_v<TupleT>)>
struct Next
{
    using type = std::tuple_element_t<INDEX + 1, TupleT>;
};

template <typename T, std::size_t INDEX, typename TupleT>
struct Next<T, INDEX, TupleT, true>
{
    using type = void;
};

template 
<
    typename T, 
    std::size_t INDEX, 
    typename TupleT
>
struct Map_F2
{
    using type = std::pair<T, typename Next<T, INDEX, TupleT>::type>;
};

TEST_CASE("[metaxxa::Map]")
{
    using T = TypeTuple<char, int, double, short, unsigned long, float>;
    using E0 = TypeTuple<char, double, double, double, double, double>;
    using E1 = TypeTuple<int, char, int, char, int, char>;

    using T1 = TypeTuple<char, int, int, short, int>;
    using E2 = TypeTuple<std::pair<char, int>, std::pair<int, int>, std::pair<int, short>,  std::pair<short, int>, std::pair<int, void>>;

    static_assert(is_same_v<Map<TypeTuple, T, Map_F0>, E0>, "Invalid map");
    static_assert(is_same_v<IndexMap<TypeTuple, T, Map_F1>, E1>, "Invalid index map");
    static_assert(is_same_v<OverallMap<TypeTuple, T1, Map_F2>, E2>, "Invalid overall map");
}