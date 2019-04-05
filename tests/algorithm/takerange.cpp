#include "../tests.h"

TEST_CASE("[metaxxa::takeRange]")
{
    using T = TypeTuple<char, short, long, size_t, int>;
    using Expected = TypeTuple<short, long>;

    static_assert(is_same_v<TakeRange<TypeTuple, T, 1, 3>, Expected>, "Invalid result of take range (1 3) types (T3)");
}