#include "../tests.h"

TEST_CASE("[metaxxa::invoke_functions]")
{
    SECTION("No func, no args")
    {
        Tuple tuple(112, 3.12, 'e');

        invoke_functions(tuple);
    }

    SECTION("No func, some args")
    {
        Tuple tuple(112, 3.12, 'e');

        invoke_functions(tuple, "Hello");
    }

    SECTION("Only funcs, no args")
    {
        bool calls[3] = { false, false, false };

        Tuple tuple
        (
            [&]() { calls[0] = true; },
            [&](int, char) { calls[1] = true; },
            [&](double) { calls[2] = true; }
        );

        invoke_functions(tuple);

        REQUIRE(calls[0]);
        REQUIRE(!calls[1]);
        REQUIRE(!calls[2]);
    }

    SECTION("Only funcs, double arg")
    {
        bool calls[5] = { false, false, false, false, false };

        Tuple tuple
        (
            [&]()            { calls[0] = true; },
            [&](int, char)   { calls[1] = true; },
            [&](double)      { calls[2] = true; },
            [&](int, char)   { calls[3] = true; },
            [&](long double) { calls[4] = true; }
        );

        invoke_functions(tuple, 3.14);

        REQUIRE(!calls[0]);
        REQUIRE(!calls[1]);
        REQUIRE(calls[2]);
        REQUIRE(!calls[3]);
        REQUIRE(calls[4]);
    }

    SECTION("Only funcs, int, char args")
    {
        bool calls[5] = { false, false, false, false, false };

        Tuple tuple
        (
            [&]()            { calls[0] = true; },
            [&](int, char)   { calls[1] = true; },
            [&](double)      { calls[2] = true; },
            [&](int, char)   { calls[3] = true; },
            [&](long double) { calls[4] = true; }
        );

        invoke_functions(tuple, 42, 'z');

        REQUIRE(!calls[0]);
        REQUIRE(calls[1]);
        REQUIRE(!calls[2]);
        REQUIRE(calls[3]);
        REQUIRE(!calls[4]);
    }
}