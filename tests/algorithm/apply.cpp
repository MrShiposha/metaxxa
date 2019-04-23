#include "../tests.h"

TEST_CASE("[metaxxa::apply]")
{
    Tuple<int, short, char> t(1, short(2), char(3));

    auto r = metaxxa::apply([](auto... t) { return (0 + ... + t); }, t);

    REQUIRE(r == 6);
}