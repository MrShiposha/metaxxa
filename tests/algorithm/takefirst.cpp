#include "../tests.h"

TEST_CASE("[metaxxa::TakeFirst]")
{
    using T0 = TypeTuple<>;
    using T1 = TypeTuple<int>;
    using T2 = TypeTuple<double, float>;
    using T3 = TypeTuple<char, short, long>;

    SECTION("Take 0")
    {
        static_assert(is_same_v<TakeFirst<TypeTuple, T0, 0>, T0>, "Invalid result of take first 0 types (T0)");
        static_assert(is_same_v<TakeFirst<TypeTuple, T1, 0>, T0>, "Invalid result of take first 0 types (T1)");
        static_assert(is_same_v<TakeFirst<TypeTuple, T2, 0>, T0>, "Invalid result of take first 0 types (T2)");
        static_assert(is_same_v<TakeFirst<TypeTuple, T3, 0>, T0>, "Invalid result of take first 0 types (T3)");
    }

    SECTION("Take 1")
    {
        static_assert(is_same_v<TakeFirst<TypeTuple, T1, 1>, T1>, "Invalid result of take first 1 type (T1)");
        static_assert(is_same_v<TakeFirst<TypeTuple, T2, 1>, TypeTuple<double>>, "Invalid result of take first 1 type (T2)");
        static_assert(is_same_v<TakeFirst<TypeTuple, T3, 1>, TypeTuple<char>>, "Invalid result of take first 1 type (T3)");
    }

    SECTION("Take 2")
    {
        static_assert(is_same_v<TakeFirst<TypeTuple, T2, 2>, T2>, "Invalid result of take first 2 types (T2)");
        static_assert(is_same_v<TakeFirst<TypeTuple, T3, 2>, TypeTuple<char, short>>, "Invalid result of take first 2 types (T3)");
    }

    SECTION("Take 3")
    {
        static_assert(is_same_v<TakeFirst<TypeTuple, T3, 3>, T3>, "Invalid result of take first 3 types (T3)");
    }
}