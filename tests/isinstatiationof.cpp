#include "tests.h"

template <typename T>
class T1 {};

template <typename T, typename U>
class T2 {};

TEST_CASE("[metaxxa::is_instatiation_of]")
{
    using namespace metaxxa;

    static_assert(is_instatiation_of<T1<int>, T1>());
    static_assert(!is_instatiation_of<T1<int>, T2>());
    static_assert(!is_instatiation_of<int, T1>());

    static_assert(is_instatiation_of<T2<int,  char>, T2>());
    static_assert(!is_instatiation_of<T2<int, char>, T1>());
}