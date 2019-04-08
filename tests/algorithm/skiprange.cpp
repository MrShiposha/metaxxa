#include "../tests.h"

#include <iostream>

TEST_CASE("[metaxxa::SkipRange]")
{
    using T = TypeTuple<char, short, long, size_t, int>;
    using Expected = TypeTuple<char, size_t, int>;

    static_assert(is_same_v<SkipRange<TypeTuple, T, 1, 3>, Expected>, "Invalid result of skip range (1 3)");
}