#ifndef METAXXA_CONTAINS_H
#define METAXXA_CONTAINS_H

#include <type_traits>

#include "../typetuple.h"
#include "../moveparameters.h"
#include "../if.h"

namespace metaxxa
{
    namespace detail
    {
        template
        <
            typename TupleT,
            typename Type,
            std::size_t... INDICES
        >
        constexpr bool contains(std::index_sequence<INDICES...>)
        {
            return (false || ... || std::is_same_v<std::tuple_element_t<INDICES, TupleT>, Type>);
        }
    }

    template
    <
        typename TupleT,
        typename Type
    >
    constexpr bool contains()
    {
        using Tuple = MoveParameters<TypeTuple, TupleT>;        

        return detail::contains<Tuple, Type>(std::make_index_sequence<std::tuple_size_v<Tuple>>());
    }

    template
    <
        typename TupleT,
        typename... Types
    >
    constexpr bool contains_all()
    {
        using Tuple = MoveParameters<TypeTuple, TupleT>;

        return (true && ... && contains<Tuple, Types>());
    }

    template <typename TupleT, typename T>
    using Contains = typename If<contains<TupleT, T>()>
        ::template Then<std::true_type>
        ::template Else<std::false_type>
        ::Type;

    template <typename TupleT, typename... Ts>
    using ContainsAll = typename If<contains_all<TupleT, Ts...>()>
        ::template Then<std::true_type>
        ::template Else<std::false_type>
        ::Type;
}

#endif // METAXXA_CONTAINS_H