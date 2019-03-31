#include "../tests.h"

TEST_CASE("[metaxxa::SkipLast]")
{
    using T0 = StaticTuple<>;
    using T1 = StaticTuple<int>;
    using T2 = StaticTuple<double, float>;
    using T3 = StaticTuple<char, short, long>;

    SECTION("Skip 0")
    {
        static_assert(is_same_v<SkipLast<StaticTuple, T0, 0>, T0>, "Invalid result of skip last 0 types (T0)");
        static_assert(is_same_v<SkipLast<StaticTuple, T1, 0>, T1>, "Invalid result of skip last 0 types (T1)");
        static_assert(is_same_v<SkipLast<StaticTuple, T2, 0>, T2>, "Invalid result of skip last 0 types (T2)");
        static_assert(is_same_v<SkipLast<StaticTuple, T3, 0>, T3>, "Invalid result of skip last 0 types (T3)");
    }

    SECTION("Skip 1")
    {
        static_assert(is_same_v<SkipLast<StaticTuple, T1, 1>, T0>, "Invalid result of skip last 1 type (T1)");
        static_assert(is_same_v<SkipLast<StaticTuple, T2, 1>, StaticTuple<double>>, "Invalid result of skip last 1 type (T2)");
        static_assert(is_same_v<SkipLast<StaticTuple, T3, 1>, StaticTuple<char, short>>, "Invalid result of skip last 1 type (T3)");
    }

    SECTION("Skip 2")
    {
        static_assert(is_same_v<SkipLast<StaticTuple, T2, 2>, T0>, "Invalid result of skip last 2 types (T2)");
        static_assert(is_same_v<SkipLast<StaticTuple, T3, 2>, StaticTuple<char>>, "Invalid result of skip last 2 types (T3)");
    }

    SECTION("Skip 3")
    {
        static_assert(is_same_v<SkipLast<StaticTuple, T3, 3>, T0>, "Invalid result of skip last 3 types (T3)");
    }
}