#include "../tests.h"

TEST_CASE("[metaxxa::Concat]")
{
    SECTION("Empty concat")
    {
        using R = Concat<TypeList>;
        static_assert(is_same_v<R, Nil>, "Invalid result of Concat");
    }

    SECTION("Unary concat")
    {
        using R = Concat<TypeList, TypeList<int, double>>;
        static_assert(is_same_v<R, TypeList<int, double>>, "Invalid result of Concat");
    }

    SECTION("Binary concat")
    {
        using R = Concat<TypeList, TypeList<int, double>, TypeList<char, short>>;
        static_assert(is_same_v<R, TypeList<int, double, char, short>>, "Invalid result of Concat");
    }

    SECTION("Multiple concat")
    {
        using R = Concat<TypeList, TypeList<int, double>, TypeList<char, short>, TypeList<void, long>>;
        static_assert(is_same_v<R, TypeList<int, double, char, short, void, long>>, "Invalid result of Concat");
    }
}