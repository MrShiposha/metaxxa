#include <iostream>
#include <tuple>

#include "../include/metaxxa.h"

int main()
{
    using namespace metaxxa;

    static_assert(std::is_same_v<typename List<int, char, double>::Head, int>);
    static_assert(std::is_same_v<typename List<int, char, double>::Tail, List<char, double>>);

    static_assert(std::is_same_v<typename List<char, double>::Head, char>);
    static_assert(std::is_same_v<typename List<char, double>::Tail, List<double>>);

    static_assert(std::is_same_v<typename List<double>::Head, double>);
    static_assert(std::is_same_v<typename List<double>::Tail, Nil>);


    static_assert(std::tuple_size_v<List<>> == 0);
    static_assert(std::tuple_size_v<List<int>> == 1);
    static_assert(std::tuple_size_v<List<int, char>> == 2);

    static_assert(std::is_same_v<std::tuple_element_t<0, List<int, char, double>>, int>);
    static_assert(std::is_same_v<std::tuple_element_t<1, List<int, char, double>>, char>);
    static_assert(std::is_same_v<std::tuple_element_t<2, List<int, char, double>>, double>);


    using T1 = StaticTuple<int, char>;
    using T2 = StaticTuple<double, float>;
    using T3 = StaticTuple<size_t>;
    using E = StaticTuple<>;

    static_assert(E::is_empty());
    static_assert(E::size() == 0);

    static_assert(!T1::is_empty());
    static_assert(T1::size() == 2);
    static_assert(std::is_same_v<T1::template Get<0>, int>);
    static_assert(std::is_same_v<T1::template Get<1>, char>);

    static_assert(!T2::is_empty());
    static_assert(T2::size() == 2);
    static_assert(std::is_same_v<T2::template Get<0>, double>);
    static_assert(std::is_same_v<T2::template Get<1>, float>);


    using R = T1::template Concat<T2>
                ::template Concat<T3>
                ::template Concat<E>;

    static_assert(!R::is_empty());
    static_assert(R::size() == 5);
    static_assert(std::is_same_v<R::template Get<0>, int>);
    static_assert(std::is_same_v<R::template Get<1>, char>);
    static_assert(std::is_same_v<R::template Get<2>, double>);
    static_assert(std::is_same_v<R::template Get<3>, float>);
    static_assert(std::is_same_v<R::template Get<4>, size_t>);

    return 0;
}