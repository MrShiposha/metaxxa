#include "tests.h"

TEST_CASE("List head/tail", "[metaxxa::List]")
{
    SECTION("Empty list")
    {
        static_assert(is_same_v<typename List<>::Head, Nil>, "Invalid Head of empty List");
        static_assert(is_same_v<typename List<>::Tail, Nil>, "Invalid Tail of empty List");
    }

    SECTION("Nil")
    {
        static_assert(is_same_v<typename Nil::Head, Nil>, "Invalid Head of Nil");
        static_assert(is_same_v<typename Nil::Tail, Nil>, "Invalid Tail of Nil");
    }

    SECTION("Nil mupltiple Head/Tail")
    {
        static_assert(is_same_v<typename Nil::Head::Head, Nil>, "Invalid Head::Head of Nil");
        static_assert(is_same_v<typename Nil::Tail::Tail, Nil>, "Invalid Tail::Tail of Nil");

        static_assert(is_same_v<typename Nil::Head::Tail, Nil>, "Invalid Head::Head of Nil");
        static_assert(is_same_v<typename Nil::Tail::Head, Nil>, "Invalid Tail::Tail of Nil");

        static_assert(is_same_v<typename Nil::Head::Head::Head, Nil>, "Invalid Head::Head::Head of Nil");
        static_assert(is_same_v<typename Nil::Tail::Tail::Tail, Nil>, "Invalid Tail::Tail::Tail of Nil");
    }

    SECTION("List with size == 1")
    {
        static_assert(is_same_v<typename List<char>::Head, char>, "Invalid Head of List with size == 1");
        static_assert(is_same_v<typename List<char>::Tail, Nil>, "Invalid Tail of List with size == 1");
    }

    SECTION("List with size == 2")
    {
        using L = List<double, char>;

        static_assert(is_same_v<typename L::Head, double>, "Invalid Head of List with size == 2");
        static_assert(is_same_v<typename L::Tail, List<char>>, "Invalid Tail of List with size == 2");

        using LTail = typename L::Tail;

        static_assert(is_same_v<typename LTail::Head, char>, "Invalid Head of List with size == 2");
        static_assert(is_same_v<typename LTail::Tail, Nil>, "Invalid Tail of List with size == 2");
    }
}

TEST_CASE("List size", "[metaxxa::List]")
{
    static_assert(tuple_size_v<List<>> == 0, "Invalid size of empty List");
    static_assert(tuple_size_v<Nil> == 0, "Invalid size of Nil");
    static_assert(tuple_size_v<List<char>> == 1, "Invalid size of List with size == 1");
    static_assert(tuple_size_v<List<char, double>> == 2, "Invalid size of List with size == 2");
}

TEST_CASE("List i-th element", "[metaxxa::List]")
{
    SECTION("Empty list")
    {
        static_assert(!is_valid<List<>>([](auto l) -> tuple_element_t<0, decltype(l)> {}), "There is not elements in empty List");
    }

    SECTION("Nil")
    {
        static_assert(!is_valid<Nil>([](auto l) -> tuple_element_t<0, decltype(l)> {}), "There is not elements in empty List");
    }

    SECTION("List with size == 1")
    {
        static_assert(is_same_v<tuple_element_t<0, List<char>>, char>, "Invalid 0 tuple_element of List with size == 1");
        static_assert(!is_valid<List<char>>([](auto l) -> tuple_element_t<1, decltype(l)> {}), "element 1 is not exists in List with size == 1");
    }

    SECTION("List with size == 2")
    {
        using L = List<double, char>;

        static_assert(is_same_v<tuple_element_t<0, L>, double>, "Invalid 0 tuple_element of List with size == 2");
        static_assert(is_same_v<tuple_element_t<1, L>, char>, "Invalid 1 tuple_element of List with size == 2");
        static_assert(!is_valid<L>([](auto l) -> tuple_element_t<2, decltype(l)> {}), "element 2 is not exists in List with size == 2");
    }
}