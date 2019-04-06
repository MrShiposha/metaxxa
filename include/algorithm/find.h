#ifndef METAXXA_ALGORITHM_FIND_H
#define METAXXA_ALGORITHM_FIND_H

#include <type_traits>

namespace metaxxa
{
    namespace detail
    {
        template
        <
            typename TupleT,
            template <typename T> typename Functor,
            std::size_t N   = 0,
            bool PREV_FOUND = false,
            bool ENOUGH     = (N >= std::tuple_size_v<TupleT>)
        >
        struct Find : Find
        <
            TupleT, 
            Functor,
            N + 1,
            Functor<std::tuple_element_t<N, TupleT>>::value(),
            N + 1 >= std::tuple_size_v<TupleT>
        >
        {};

        template
        <
            typename TupleT,
            template <typename T> typename Functor,
            std::size_t N,
            bool ENOUGH
        >
        struct Find
        <
            TupleT,
            Functor,
            N,
            true,
            ENOUGH
        >
        {
            static constexpr bool FOUND = true;
            static constexpr std::size_t INDEX = N - 1;

            using Type = std::tuple_element_t<INDEX, TupleT>;

            template <typename T>
            using TypeOr = Type;
        };
        
        template
        <
            typename TupleT,
            template <typename T> typename Functor,
            std::size_t N
        >
        struct Find
        <
            TupleT,
            Functor,
            N,
            false,
            true
        >
        {
            static constexpr bool FOUND = false;

            template <typename T>
            using TypeOr = T;
        };
    }

    template 
    <
        typename TupleT,
        template <typename T> typename Functor
    >
    using Find = detail::Find<TupleT, Functor>;
}

#endif // METAXXA_ALGORITHM_FIND_H