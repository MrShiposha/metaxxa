#ifndef METAXXA_ISAPPLICABLE_H
#define METAXXA_ISAPPLICABLE_H

#include <type_traits>

namespace metaxxa
{
    namespace detail
    {
        template <typename Callable, typename TupleT, std::size_t... INDICES>
        constexpr bool is_applicable(std::index_sequence<INDICES...>)
        {
            return std::is_invocable_v<Callable, std::tuple_element_t<INDICES, TupleT>...>;
        }
    }

    template <typename Callable, typename TupleT>
    constexpr bool is_applicable()
    {
        return detail::is_applicable<Callable, TupleT>(std::make_index_sequence<std::tuple_size_v<TupleT>>());
    }
}

#endif // METAXXA_ISAPPLICABLE_H