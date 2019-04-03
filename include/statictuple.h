#ifndef METAXXA_STATIC_TUPLE_H
#define METAXXA_STATIC_TUPLE_H

#include "typelist.h"

namespace metaxxa
{
    template <typename... Args>
    class StaticTuple;

    namespace detail
    {
        template <typename... Args>
        struct TupleConcatenator
        {
            template <typename... RHSArgs>
            static constexpr auto result_tuple(StaticTuple<RHSArgs...> &&) 
                -> StaticTuple<Args..., RHSArgs...>;
        };
    }

    template <typename... Args>
    class StaticTuple : public TypeList<Args...>
    {
    public:
        using List = metaxxa::TypeList<Args...>;

        template <std::size_t INDEX>
        using Get = typename std::tuple_element_t<INDEX, List>;

        template <typename RHSTuple>
        using Concat = decltype(detail::TupleConcatenator<Args...>::template result_tuple(std::declval<RHSTuple>()));

        constexpr StaticTuple() = default;

        static constexpr bool is_empty();

        static constexpr std::size_t get_size();

        static constexpr std::size_t size();
    };
}

namespace std
{
    template <typename... Args>
    class tuple_size<metaxxa::StaticTuple<Args...>>
        : public std::integral_constant<std::size_t, sizeof...(Args)>
    {};

    template <>
    class tuple_size<metaxxa::StaticTuple<>>
        : public std::integral_constant<std::size_t, 0>
    {};

    template <size_t INDEX, typename... Args>
	class tuple_element<INDEX, metaxxa::StaticTuple<Args...>>
	{
	public:
		using type = tuple_element_t<INDEX, typename metaxxa::StaticTuple<Args...>::List>;
	};
}

#endif // METAXXA_STATIC_TUPLE_H
