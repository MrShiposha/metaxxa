#include "tests.h"

using TestSwitch = 
    typename Switch<std::size_t>
    ::template Case<1, int>
    ::template Case<500, short>
    ::template Case<42, double>;

template <std::size_t X>
using TestSwitchType = typename TestSwitch::template Type<X>;

using TestSwitchDefault = 
    typename Switch<std::size_t>
        ::template Case<1, int>
        ::template Case<500, short>
        ::template Case<42, double>
        ::template Default<char>;

template <std::size_t X>
using TestSwitchDefaultType = typename TestSwitchDefault::template Type<X>;

TEST_CASE("[metaxxa::Switch]")
{
    using Cases = TypeList<SwitchCase<std::size_t, 1, int>, SwitchCase<std::size_t, 500, short>, SwitchCase<std::size_t, 42, double>>;
    using CasesWithDefault = Concat<TypeList, Cases, TemplateContainer<SwitchDefaultCase<std::size_t, char>>>;

    SECTION("Type")
    {
        static_assert(is_same_v<TestSwitchType<1>, int>, "Invalid TestSwitchType<1>");
        static_assert(is_same_v<TestSwitchType<500>, short>, "Invalid TestSwitchType<500>");
        static_assert(is_same_v<TestSwitchType<42>, double>, "Invalid TestSwitchType<42>");
        static_assert(is_same_v<typename TestSwitch::Cases, Cases>, "Invalid TestSwitch::Cases");
    }

    SECTION("DefaultType")
    {
        static_assert(is_same_v<TestSwitchDefaultType<1>, int>, "Invalid TestSwitchDefaultType<1>");
        static_assert(is_same_v<TestSwitchDefaultType<500>, short>, "Invalid TestSwitchDefaultType<500>");
        static_assert(is_same_v<TestSwitchDefaultType<42>, double>, "Invalid TestSwitchDefaultType<42>");
        static_assert(is_same_v<TestSwitchDefaultType<111>, char>, "Invalid TestSwitchDefaultType<111>");
        static_assert(is_same_v<typename TestSwitchDefault::Cases, CasesWithDefault>, "Invalid TestSwitchDefault::Cases");
    }
}