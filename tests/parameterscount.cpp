#include "tests.h"

TEST_CASE("[metaxxa::ParametersCount]")
{
    using L0 = List<>;
    using L1 = List<int>;
    using L2 = List<double, char>;

    using T0 = ParametersCount<L0>;
    using T1 = ParametersCount<L1>;
    using T2 = ParametersCount<L2>;

    static_assert(T0::value == 0, "Invalid parameters count of T0");
    static_assert(T1::value == 1, "Invalid parameters count of T1");
    static_assert(T2::value == 2, "Invalid parameters count of T2");

    static_assert(T0::value == parameters_count<L0>(), "T0::value != parameters_count<L0>()");
    static_assert(T1::value == parameters_count<L1>(), "T1::value != parameters_count<L1>()");
    static_assert(T2::value == parameters_count<L2>(), "T2::value != parameters_count<L2>()");
}