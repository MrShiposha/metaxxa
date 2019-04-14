#include "tests.h"

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