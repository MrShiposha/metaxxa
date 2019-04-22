#include "tests.h"

#include <chrono>
#include <iostream>
#include <tuple>

struct ToReconstruct
{
    ToReconstruct()
    {
        ++constructs;
    }

    ToReconstruct(int, char)
    {
        ++constructs_with_args;
    }

    ~ToReconstruct()
    {
        ++destructs;
    }

    static int constructs;
    static int constructs_with_args;
    static int destructs;
};

int ToReconstruct::constructs = 0;
int ToReconstruct::constructs_with_args = 0;
int ToReconstruct::destructs = 0;


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
}

TEST_CASE("Tuple reconstruct", "[metaxxa::Tuple]")
{
    Tuple<ToReconstruct> tuple;

    REQUIRE(ToReconstruct::constructs == 1);

    tuple.reconstruct<0>();

    REQUIRE(ToReconstruct::constructs == 2);
    REQUIRE(ToReconstruct::destructs == 1);

    tuple.reconstruct<0, ReconstructOnly>();

    REQUIRE(ToReconstruct::constructs == 3);
    REQUIRE(ToReconstruct::destructs == 1);

    tuple.reconstruct<0>(1, 'a');

    REQUIRE(ToReconstruct::constructs_with_args == 1);
    REQUIRE(ToReconstruct::destructs == 2);

    tuple.reconstruct<0, ReconstructOnly>(1, 'a');

    REQUIRE(ToReconstruct::constructs_with_args == 2);
    REQUIRE(ToReconstruct::destructs == 2);
}