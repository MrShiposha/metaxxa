#include "../tests.h"

TEST_CASE("[metaxxa::TakeLast]")
{
    using T0 = TypeTuple<>;
    using T1 = TypeTuple<int>;
    using T2 = TypeTuple<double, float>;
    using T3 = TypeTuple<char, short, long>;

    SECTION("Take 0")
    {
        static_assert(is_same_v<TakeLast<TypeTuple, T0, 0>, T0>, "Invalid result of take last 0 types (T0)");
        static_assert(is_same_v<TakeLast<TypeTuple, T1, 0>, T0>, "Invalid result of take last 0 types (T1)");
        static_assert(is_same_v<TakeLast<TypeTuple, T2, 0>, T0>, "Invalid result of take last 0 types (T2)");
        static_assert(is_same_v<TakeLast<TypeTuple, T3, 0>, T0>, "Invalid result of take last 0 types (T3)");
    }

    SECTION("Take 1")
    {
        static_assert(is_same_v<TakeLast<TypeTuple, T1, 1>, T1>, "Invalid result of take last 1 type (T1)");
        static_assert(is_same_v<TakeLast<TypeTuple, T2, 1>, TypeTuple<float>>, "Invalid result of take last 1 type (T2)");
        static_assert(is_same_v<TakeLast<TypeTuple, T3, 1>, TypeTuple<long>>, "Invalid result of take last 1 type (T3)");
    }

    SECTION("Take 2")
    {
        static_assert(is_same_v<TakeLast<TypeTuple, T2, 2>, T2>, "Invalid result of take last 2 types (T2)");
        static_assert(is_same_v<TakeLast<TypeTuple, T3, 2>, TypeTuple<short, long>>, "Invalid result of take last 2 types (T3)");
    }

    SECTION("Take 3")
    {
        static_assert(is_same_v<TakeLast<TypeTuple, T3, 3>, T3>, "Invalid result of take last 3 types (T3)");
    }
}