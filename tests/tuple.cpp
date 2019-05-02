#include "tests.h"

#include <chrono>
#include <iostream>
#include <tuple>

TEST_CASE("Tuple creation/assign", "[metaxxa::Tuple]")
{
    SECTION("Default")
    {
        Tuple<int, char, double> t;

        REQUIRE(t.get<0>() == 0);
        REQUIRE(t.get<1>() == '\0');
        REQUIRE(t.get<2>() == Approx(0.0));
    }

    SECTION("Args")
    {
        Tuple<int, char, double> t(42, 'a', 3.14);

        REQUIRE(t.get<0>() == 42);
        REQUIRE(t.get<1>() == 'a');
        REQUIRE(t.get<2>() == Approx(3.14));
    }

    SECTION("Copy")
    {
        Tuple<int, char, double> t(42, 'a', 3.14);
        Tuple<int, char, double> copy(t);

        REQUIRE(copy.get<0>() == 42);
        REQUIRE(copy.get<1>() == 'a');
        REQUIRE(copy.get<2>() == Approx(3.14));
    }

    SECTION("Copy from pair")
    {
        std::pair<int, char> t(42, 'a');
        TupleFrom<decltype(t)> copy(t);

        REQUIRE(copy.get<0>() == 42);
        REQUIRE(copy.get<1>() == 'a');
    }

    SECTION("Copy from std tuple")
    {
        std::tuple<int, char, double> t(42, 'a', 3.14);
        TupleFrom<decltype(t)> copy(t);

        REQUIRE(copy.get<0>() == 42);
        REQUIRE(copy.get<1>() == 'a');
        REQUIRE(copy.get<2>() == Approx(3.14));
    }

    SECTION("Copy from tuple")
    {
        Tuple<int, char, double> t(42, 'a', 3.14);
        Tuple copy(t);

        REQUIRE(copy.get<0>() == 42);
        REQUIRE(copy.get<1>() == 'a');
        REQUIRE(copy.get<2>() == Approx(3.14));
    }

    SECTION("Copy assign")
    {
        Tuple<int, char, double> t(42, 'a', 3.14);
        Tuple<int, char, double> copy;

        copy = t;

        REQUIRE(copy.get<0>() == 42);
        REQUIRE(copy.get<1>() == 'a');
        REQUIRE(copy.get<2>() == Approx(3.14));
    }

    SECTION("Copy assign from pair")
    {
        std::pair<int, char> t(42, 'a');
        Tuple<int, char> copy;

        copy = t;

        REQUIRE(copy.get<0>() == 42);
        REQUIRE(copy.get<1>() == 'a');
    }

    SECTION("Move assign")
    {
        Tuple<int, char, double> t(42, 'a', 3.14);
        Tuple<int, char, double> copy;

        copy = std::move(t);

        REQUIRE(copy.get<0>() == 42);
        REQUIRE(copy.get<1>() == 'a');
        REQUIRE(copy.get<2>() == Approx(3.14));
    }
}

TEST_CASE("Tuple algorithms", "[metaxxa::Tuple]")
{
    SECTION("only indices")
    {
        Tuple<int, char, double> t_src(42, 'a', 3.14);
        Tuple<int, double> t = t_src.template only_indices<0, 2>();

        REQUIRE(t.get<0>() == 42);
        REQUIRE(t.get<1>() == Approx(3.14));
    }

    SECTION("take range")
    {
        Tuple<int, char, double, int, short> t_src(42, 'a', 3.14, 112, short(-1));
        Tuple<char, double, int> t = t_src.template take_range<1, 4>();

        REQUIRE(t.get<0>() == 'a');
        REQUIRE(t.get<1>() == Approx(3.14));
        REQUIRE(t.get<2>() == 112);
    }

    SECTION("take range shared")
    {
        Tuple<int, char, double, int, short> t_src(42, 'a', 3.14, 112, short(-1));
        Tuple<char, double, int> t = t_src.template take_range_shared<1, 4>();

        REQUIRE(t.get(0) == t_src.get(1));
        REQUIRE(t.get<0>() == 'a');
        REQUIRE(t.get<1>() == Approx(3.14));
        REQUIRE(t.get<2>() == 112);
    }

    SECTION("take first")
    {
        Tuple<int, char, double, int, short> t_src(42, 'a', 3.14, 112, short(-1));
        Tuple<int, char, double> t = t_src.template take_first<3>();

        REQUIRE(t.get<0>() == 42);
        REQUIRE(t.get<1>() == 'a');
        REQUIRE(t.get<2>() == Approx(3.14));
    }

    SECTION("take first shared")
    {
        Tuple<int, char, double, int, short> t_src(42, 'a', 3.14, 112, short(-1));
        Tuple<int, char, double> t = t_src.template take_first_shared<3>();

        REQUIRE(t.get(0) == t_src.get(0));
        REQUIRE(t.get<0>() == 42);
        REQUIRE(t.get<1>() == 'a');
        REQUIRE(t.get<2>() == Approx(3.14));
    }

    SECTION("take last")
    {
        Tuple<int, char, double, int, short> t_src(42, 'a', 3.14, 112, short(-1));
        Tuple<double, int, short> t = t_src.template take_last<3>();

        REQUIRE(t.get<0>() == Approx(3.14));
        REQUIRE(t.get<1>() == 112);
        REQUIRE(t.get<2>() == short(-1));
    }

    SECTION("take last shared")
    {
        Tuple<int, char, double, int, short> t_src(42, 'a', 3.14, 112, short(-1));
        Tuple<double, int, short> t = t_src.template take_last_shared<3>();

        REQUIRE(t.get(0) == t_src.get(2));
        REQUIRE(t.get<0>() == Approx(3.14));
        REQUIRE(t.get<1>() == 112);
        REQUIRE(t.get<2>() == short(-1));
    }

    SECTION("skip first")
    {
        Tuple<int, char, double, int, short> t_src(42, 'a', 3.14, 112, short(-1));
        Tuple<int, short> t = t_src.template skip_first<3>();

        REQUIRE(t.get<0>() == 112);
        REQUIRE(t.get<1>() == short(-1));
    }

    SECTION("skip first shared")
    {
        Tuple<int, char, double, int, short> t_src(42, 'a', 3.14, 112, short(-1));
        Tuple<int, short> t = t_src.template skip_first_shared<3>();

        REQUIRE(t.get(0) == t_src.get(3));
        REQUIRE(t.get<0>() == 112);
        REQUIRE(t.get<1>() == short(-1));
    }

    SECTION("skip last")
    {
        Tuple<int, char, double, int, short> t_src(42, 'a', 3.14, 112, short(-1));
        Tuple<int, char> t = t_src.template skip_last<3>();

        REQUIRE(t.get<0>() == 42);
        REQUIRE(t.get<1>() == 'a');
    }

    SECTION("skip last shared")
    {
        Tuple<int, char, double, int, short> t_src(42, 'a', 3.14, 112, short(-1));
        Tuple<int, char> t = t_src.template skip_last_shared<3>();

        REQUIRE(t.get(0) == t_src.get(0));
        REQUIRE(t.get<0>() == 42);
        REQUIRE(t.get<1>() == 'a');
    }
}