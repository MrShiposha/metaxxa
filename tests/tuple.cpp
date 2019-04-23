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