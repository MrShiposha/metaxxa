#include "tests.h"

TEST_CASE("[metaxxa::MoveParameters]")
{
    using L0 = TypeList<>;
    using L1 = TypeList<int>;
    using L2 = TypeList<char, float>;

    using R0 = MoveParameters<TypeList, TypeTuple<>>;
    using R1 = MoveParameters<TypeList, TypeTuple<int>>;
    using R2 = MoveParameters<TypeList, TypeTuple<char, float>>;

    static_assert(std::is_same_v<L0, R0>, "Invalid R0");
    static_assert(std::is_same_v<L1, R1>, "Invalid R1");
    static_assert(std::is_same_v<L2, R2>, "Invalid R2");
}