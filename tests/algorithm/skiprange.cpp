#include "../tests.h"

TEST_CASE("[metaxxa::SkipRange]")
{
    using T = StaticTuple<char, short, long, size_t, int>;
    using Expected = StaticTuple<short, long>;

    static_assert(is_same_v<SkipRange<StaticTuple, T, 1, 3>, Expected>, "Invalid result of skip range (1 3) types (T3)");
}