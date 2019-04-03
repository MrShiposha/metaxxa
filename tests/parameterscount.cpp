#include "tests.h"

TEST_CASE("[metaxxa::ParametersCount]")
{
    using L0 = TypeList<>;
    using L1 = TypeList<int>;
    using L2 = TypeList<double, char>;

    using T0 = ParametersCount<L0>;
    using T1 = ParametersCount<L1>;
    using T2 = ParametersCount<L2>;

    static_assert(T0::VALUE == 0, "Invalid parameters count of T0");
    static_assert(T1::VALUE == 1, "Invalid parameters count of T1");
    static_assert(T2::VALUE == 2, "Invalid parameters count of T2");

    static_assert(T0::VALUE == parameters_count<L0>(), "T0::VALUE != parameters_count<L0>()");
    static_assert(T1::VALUE == parameters_count<L1>(), "T1::VALUE != parameters_count<L1>()");
    static_assert(T2::VALUE == parameters_count<L2>(), "T2::VALUE != parameters_count<L2>()");
}