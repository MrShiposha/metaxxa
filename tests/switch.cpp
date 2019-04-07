#include "tests.h"

#include <iostream>

template <std::size_t X>
    using TestSwitchType = 
        typename Switch<std::size_t, X>
            ::template Case<1, int>
            ::template Case<500, short>
            ::template Case<42, double>
            ::Type;

template <std::size_t X>
    using TestSwitchDefaultType = 
        typename Switch<std::size_t, X>
            ::template Case<1, int>
            ::template Case<500, short>
            ::template Case<42, double>
            ::template DefaultType<char>;

TEST_CASE("[metaxxa::Switch]")
{
    SECTION("Type")
    {
        static_assert(is_same_v<TestSwitchType<1>, int>, "Invalid TestSwitchType<1>");
        static_assert(is_same_v<TestSwitchType<500>, short>, "Invalid TestSwitchType<500>");
        static_assert(is_same_v<TestSwitchType<42>, double>, "Invalid TestSwitchType<42>");
    }

    SECTION("DefaultType")
    {
        static_assert(is_same_v<TestSwitchDefaultType<1>, int>, "Invalid TestSwitchDefaultType<1>");
        static_assert(is_same_v<TestSwitchDefaultType<500>, short>, "Invalid TestSwitchDefaultType<500>");
        static_assert(is_same_v<TestSwitchDefaultType<42>, double>, "Invalid TestSwitchDefaultType<42>");
        static_assert(is_same_v<TestSwitchDefaultType<111>, char>, "Invalid TestSwitchDefaultType<111>");
    }
}