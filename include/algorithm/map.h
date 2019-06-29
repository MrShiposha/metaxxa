#ifndef METAXXA_ALGORITHM_MAP_H
#define METAXXA_ALGORITHM_MAP_H

#include <type_traits>
#include <utility>

#include "concat.h"

namespace metaxxa
{
    namespace detail
    {
        template 
        <
            template <typename...> typename Template,
            typename TupleT,
            template <typename T> typename Functor,
            std::size_t... INDICES
        >
        constexpr auto map_types(std::index_sequence<INDICES...>)
            -> Concat
                <
                    Template,  
                    TemplateContainer<typename Functor<std::tuple_element_t<INDICES, TupleT>>::type...>
                >;

        template 
        <
            template <typename...> typename Template,
            typename TupleT,
            template <typename T, std::size_t INDEX> typename Functor,
            std::size_t... INDICES
        >
        constexpr auto index_map_types(std::index_sequence<INDICES...>)
            -> Concat
                <
                    Template,  
                    TemplateContainer<typename Functor<std::tuple_element_t<INDICES, TupleT>, INDICES>::type...>
                >;

        template 
        <
            template <typename...> typename Template,
            typename TupleT,
            template <typename T, std::size_t INDEX, typename SrcTuple> typename Functor,
            std::size_t... INDICES
        >
        constexpr auto overall_map_types(std::index_sequence<INDICES...>)
            -> Concat
                <
                    Template,  
                    TemplateContainer<typename Functor<std::tuple_element_t<INDICES, TupleT>, INDICES, TupleT>::type...>
                >;
    }

    template 
    <
        template <typename...> typename Template,
        typename TupleT,
        template <typename T> typename Functor
    >
    using Map = decltype
    (
        detail::map_types
        <
            Template, 
            TupleT, 
            Functor
        >(std::make_index_sequence<std::tuple_size_v<TupleT>>())
    );

    template 
    <
        template <typename...> typename Template,
        typename TupleT,
        template <typename T, std::size_t INDEX> typename Functor
    >
    using IndexMap = decltype
    (
        detail::index_map_types
        <
            Template, 
            TupleT, 
            Functor
        >(std::make_index_sequence<std::tuple_size_v<TupleT>>())
    );

    template 
    <
        template <typename...> typename Template,
        typename TupleT,
        template <typename T, std::size_t INDEX, typename SrcTuple> typename Functor
    >
    using OverallMap = decltype
    (
        detail::overall_map_types
        <
            Template, 
            TupleT, 
            Functor
        >(std::make_index_sequence<std::tuple_size_v<TupleT>>())
    );
}

#endif // METAXXA_ALGORITHM_MAP_H