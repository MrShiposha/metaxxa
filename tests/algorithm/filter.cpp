#include "../tests.h"

template <typename T>
struct Filter_F0
{
    static constexpr bool value = is_integral_v<T>;
};

template <typename T, std::size_t INDEX>
struct Filter_F1
{
    static constexpr bool value = (is_integral_v<T> || INDEX % 2 == 0);
};


template <typename T, std::size_t INDEX, typename TupleT, bool AT_BORDER = (INDEX + 1 == std::tuple_size_v<TupleT>)>
struct NextIntPair
{
    static constexpr bool value=
    ( 
           is_same_v<T, int> 
        && is_same_v<tuple_element_t<INDEX + 1, TupleT>, T>
    );
};

template <typename T, std::size_t INDEX, typename TupleT>
struct NextIntPair<T, INDEX, TupleT, true>
{
    static constexpr bool value = false;
};

template <typename T, std::size_t INDEX, typename TupleT, bool AT_BORDER = (INDEX == 0)>
struct PrevIntPair
{
    static constexpr bool value =
    (
            is_same_v<T, int> 
         && is_same_v<tuple_element_t<INDEX - 1, TupleT>, T>
    );
};

template <typename T, std::size_t INDEX, typename TupleT>
struct PrevIntPair<T, INDEX, TupleT, true>
{
    static constexpr bool value = false;
};

template 
<
    typename T, 
    std::size_t INDEX, 
    typename TupleT
>
struct Filter_F2
{
    static constexpr bool value = (NextIntPair<T, INDEX, TupleT>::value || PrevIntPair<T, INDEX, TupleT>::value);
};

TEST_CASE("[metaxxa::Filter]")
{
    using T = TypeTuple<char, int, double, short, unsigned long, float>;
    using E0 = TypeTuple<char, int, short, unsigned long>;
    using E1 = TypeTuple<char, int, double, short, unsigned long>;

    using T1 = TypeTuple<char, int, int, short, int, int, double, int>;
    using E2 = TypeTuple<int, int, int, int>;

    static_assert(is_same_v<Filter<TypeTuple, T, Filter_F0>, E0>, "Invalid filter");
    static_assert(is_same_v<IndexFilter<TypeTuple, T, Filter_F1>, E1>, "Invalid index filter");
    static_assert(is_same_v<OverallFilter<TypeTuple, T1, Filter_F2>, E2>, "Invalid overall filter");
}