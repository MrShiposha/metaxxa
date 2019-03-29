#include "statictuple.h"

namespace metaxxa
{
    template <typename... Args>
    constexpr bool StaticTuple<Args...>::is_empty()
    {
        return std::is_same_v<Car<Args...>, Nil>;
    }

    template <typename... Args>
    constexpr std::size_t StaticTuple<Args...>::get_size()
    {
        return std::tuple_size_v<StaticTuple<Args...>>;
    }

    template <typename... Args>
    constexpr std::size_t StaticTuple<Args...>::size()
    {
        return get_size();
    }
}