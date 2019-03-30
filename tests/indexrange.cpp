#include "tests.h"

TEST_CASE("[metaxxa::MakeIndexRange]")
{
    static_assert(is_same_v<MakeIndexRange<0, 5>, std::index_sequence<0, 1, 2, 3, 4>>, "Invalid seq from 0 to 5");
    static_assert(is_same_v<MakeIndexRange<1, 5>, std::index_sequence<1, 2, 3, 4>>, "Invalid seq from 1 to 5");
    static_assert(is_same_v<MakeIndexRange<2, 5>, std::index_sequence<2, 3, 4>>, "Invalid seq from 2 to 5");
    static_assert(is_same_v<MakeIndexRange<2, 4>, std::index_sequence<2, 3>>, "Invalid seq from 2 to 4");
}