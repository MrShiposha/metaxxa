#include "tests.h"

#include <vector>
#include <string>
#include <utility>

template <typename T>
    using TestSwitchType = 
        typename TypeSwitch<T>
            ::template Case<uint32_t, std::vector<T>>
            ::template Case<char, std::string>
            ::template Case<double, std::pair<int, T>>
            ::Type;

template <typename T>
    using TestSwitchDefaultType = 
        typename TypeSwitch<T>
            ::template Case<uint32_t, std::vector<T>>
            ::template Case<char, std::string>
            ::template Case<double, std::pair<int, T>>
            ::template DefaultType<void>;

TEST_CASE("[metaxxa::TypeSwitch]")
{
    SECTION("Type")
    {
        static_assert(is_same_v<TestSwitchType<uint32_t>, std::vector<uint32_t>>, "Invalid TestSwitchType<uint32_t>");
        static_assert(is_same_v<TestSwitchType<char>, std::string>, "Invalid TestSwitchType<char>");
        static_assert(is_same_v<TestSwitchType<double>, std::pair<int, double>>, "Invalid TestSwitchType<double>");
    }

    SECTION("DefaultType")
    {
        static_assert(is_same_v<TestSwitchDefaultType<uint32_t>, std::vector<uint32_t>>, "Invalid TestSwitchDefaultType<uint32_t>");
        static_assert(is_same_v<TestSwitchDefaultType<char>, std::string>, "Invalid TestSwitchDefaultType<char>");
        static_assert(is_same_v<TestSwitchDefaultType<double>, std::pair<int, double>>, "Invalid TestSwitchDefaultType<double>");
        static_assert(is_same_v<TestSwitchDefaultType<long long>, void>, "Invalid TestSwitchDefaultType<long long>");
    }
}