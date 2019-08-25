#include "tests.h"

using namespace metaxxa;

TEST_CASE("Type::parameters_count()", "[metaxxa::Type]")
{
    static_assert(Type<std::tuple<>>::parameters_count() == 0);
    static_assert(Type<std::tuple<int>>::parameters_count() == 1);
    static_assert(Type<std::tuple<int, int>>::parameters_count() == 2);
}

// TODO