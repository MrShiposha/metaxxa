#include "tests.h"

TEST_CASE("TypeList head/tail", "[metaxxa::TypeList]")
{
    SECTION("Empty list")
    {
        static_assert(is_same_v<typename TypeList<>::Head, Nil>, "Invalid Head of empty TypeList");
        static_assert(is_same_v<typename TypeList<>::Tail, Nil>, "Invalid Tail of empty TypeList");
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

    SECTION("TypeList with size == 1")
    {
        static_assert(is_same_v<typename TypeList<char>::Head, char>, "Invalid Head of TypeList with size == 1");
        static_assert(is_same_v<typename TypeList<char>::Tail, Nil>, "Invalid Tail of TypeList with size == 1");
    }

    SECTION("TypeList with size == 2")
    {
        using L = TypeList<double, char>;

        static_assert(is_same_v<typename L::Head, double>, "Invalid Head of TypeList with size == 2");
        static_assert(is_same_v<typename L::Tail, TypeList<char>>, "Invalid Tail of TypeList with size == 2");

        using LTail = typename L::Tail;

        static_assert(is_same_v<typename LTail::Head, char>, "Invalid Head of TypeList with size == 2");
        static_assert(is_same_v<typename LTail::Tail, Nil>, "Invalid Tail of TypeList with size == 2");
    }
}

TEST_CASE("TypeList size", "[metaxxa::TypeList]")
{
    static_assert(tuple_size_v<TypeList<>> == 0, "Invalid size of empty TypeList");
    static_assert(tuple_size_v<Nil> == 0, "Invalid size of Nil");
    static_assert(tuple_size_v<TypeList<char>> == 1, "Invalid size of TypeList with size == 1");
    static_assert(tuple_size_v<TypeList<char, double>> == 2, "Invalid size of TypeList with size == 2");
}

TEST_CASE("TypeList i-th element", "[metaxxa::TypeList]")
{
    SECTION("Empty list")
    {
        static_assert(!is_valid<TypeList<>>([](auto l) -> tuple_element_t<0, decltype(l)> {}), "There is not elements in empty TypeList");
    }

    SECTION("Nil")
    {
        static_assert(!is_valid<Nil>([](auto l) -> tuple_element_t<0, decltype(l)> {}), "There is not elements in empty TypeList");
    }

    SECTION("TypeList with size == 1")
    {
        static_assert(is_same_v<tuple_element_t<0, TypeList<char>>, char>, "Invalid 0 tuple_element of TypeList with size == 1");
        static_assert(!is_valid<TypeList<char>>([](auto l) -> tuple_element_t<1, decltype(l)> {}), "element 1 is not exists in TypeList with size == 1");
    }

    SECTION("TypeList with size == 2")
    {
        using L = TypeList<double, char>;

        static_assert(is_same_v<tuple_element_t<0, L>, double>, "Invalid 0 tuple_element of TypeList with size == 2");
        static_assert(is_same_v<tuple_element_t<1, L>, char>, "Invalid 1 tuple_element of TypeList with size == 2");
        static_assert(!is_valid<L>([](auto l) -> tuple_element_t<2, decltype(l)> {}), "element 2 is not exists in TypeList with size == 2");
    }
}