#include "../tests.h"

TEST_CASE("[metaxxa::SkipLast]")
{
    using T0 = TypeTuple<>;
    using T1 = TypeTuple<int>;
    using T2 = TypeTuple<double, float>;
    using T3 = TypeTuple<char, short, long>;

    SECTION("Skip 0")
    {
        static_assert(is_same_v<SkipLast<TypeTuple, T0, 0>, T0>, "Invalid result of skip last 0 types (T0)");
        static_assert(is_same_v<SkipLast<TypeTuple, T1, 0>, T1>, "Invalid result of skip last 0 types (T1)");
        static_assert(is_same_v<SkipLast<TypeTuple, T2, 0>, T2>, "Invalid result of skip last 0 types (T2)");
        static_assert(is_same_v<SkipLast<TypeTuple, T3, 0>, T3>, "Invalid result of skip last 0 types (T3)");
    }

    SECTION("Skip 1")
    {
        static_assert(is_same_v<SkipLast<TypeTuple, T1, 1>, T0>, "Invalid result of skip last 1 type (T1)");
        static_assert(is_same_v<SkipLast<TypeTuple, T2, 1>, TypeTuple<double>>, "Invalid result of skip last 1 type (T2)");
        static_assert(is_same_v<SkipLast<TypeTuple, T3, 1>, TypeTuple<char, short>>, "Invalid result of skip last 1 type (T3)");
    }

    SECTION("Skip 2")
    {
        static_assert(is_same_v<SkipLast<TypeTuple, T2, 2>, T0>, "Invalid result of skip last 2 types (T2)");
        static_assert(is_same_v<SkipLast<TypeTuple, T3, 2>, TypeTuple<char>>, "Invalid result of skip last 2 types (T3)");
    }

    SECTION("Skip 3")
    {
        static_assert(is_same_v<SkipLast<TypeTuple, T3, 3>, T0>, "Invalid result of skip last 3 types (T3)");
    }
}