#include "tests.h"

TEST_CASE("[metaxxa::MoveParameters]")
{
    using L0 = List<>;
    using L1 = List<int>;
    using L2 = List<char, float>;

    using R0 = MoveParameters<List, StaticTuple<>>;
    using R1 = MoveParameters<List, StaticTuple<int>>;
    using R2 = MoveParameters<List, StaticTuple<char, float>>;

    static_assert(std::is_same_v<L0, R0>, "Invalid R0");
    static_assert(std::is_same_v<L1, R1>, "Invalid R1");
    static_assert(std::is_same_v<L2, R2>, "Invalid R2");
}