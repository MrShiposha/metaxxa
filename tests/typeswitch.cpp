#include "tests.h"

#include <vector>
#include <string>
#include <utility>

template <typename T>
using TestSwitch = 
    typename TypeSwitch
        ::template Case<uint32_t, std::vector<T>>
        ::template Case<char, std::string>
        ::template Case<double, std::pair<int, T>>;

template <typename T>
using TestSwitchType = typename TestSwitch<T>::template Type<T>;

template <typename T>
using TestSwitchDefault = 
    typename TypeSwitch
        ::template Case<uint32_t, std::vector<T>>
        ::template Case<char, std::string>
        ::template Case<double, std::pair<int, T>>
        ::template Default<void>;

template <typename T>
using TestSwitchDefaultType = typename TestSwitchDefault<T>::template Type<T>;

TEST_CASE("[metaxxa::TypeSwitch]")
{
    using Cases_uint32_t = TypeList
    <
        TypeSwitchCase<uint32_t, std::vector<uint32_t>>, 
        TypeSwitchCase<char, std::string>, 
        TypeSwitchCase<double, std::pair<int, uint32_t>>
    >;

    using CasesWithDefault_uint32_t = Concat<TypeList, Cases_uint32_t, TemplateContainer<TypeSwitchDefaultCase<void>>>;

    SECTION("Type")
    {
        static_assert(is_same_v<TestSwitchType<uint32_t>, std::vector<uint32_t>>, "Invalid TestSwitchType<uint32_t>");
        static_assert(is_same_v<TestSwitchType<char>, std::string>, "Invalid TestSwitchType<char>");
        static_assert(is_same_v<TestSwitchType<double>, std::pair<int, double>>, "Invalid TestSwitchType<double>");
        static_assert(is_same_v<typename TestSwitch<uint32_t>::Cases, Cases_uint32_t>, "Invalid TestSwitch<uint32_t>::Cases");
    }

    SECTION("DefaultType")
    {
        static_assert(is_same_v<TestSwitchDefaultType<uint32_t>, std::vector<uint32_t>>, "Invalid TestSwitchDefaultType<uint32_t>");
        static_assert(is_same_v<TestSwitchDefaultType<char>, std::string>, "Invalid TestSwitchDefaultType<char>");
        static_assert(is_same_v<TestSwitchDefaultType<double>, std::pair<int, double>>, "Invalid TestSwitchDefaultType<double>");
        static_assert(is_same_v<TestSwitchDefaultType<long long>, void>, "Invalid TestSwitchDefaultType<long long>");
        static_assert(is_same_v<typename TestSwitchDefault<uint32_t>::Cases, CasesWithDefault_uint32_t>, "Invalid TestSwitchDefault<uint32_t>::Cases");
    }
}