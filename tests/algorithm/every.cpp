#include "../tests.h"

struct T {};

TEST_CASE("[metaxxa::Every]")
{
    static_assert(every<std::is_fundamental, std::tuple<int, char, double>>());
    static_assert(!every<std::is_fundamental, std::tuple<int, char, T>>());
}