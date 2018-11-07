#ifndef METAXXA_MOVETEMPLATETYPES_H
#define METAXXA_MOVETEMPLATETYPES_H

#include "IsTemplate.h"

namespace metaxxa::detail
{
    template <template <typename...> typename DestTemplate, template <typename...> typename SrcTemplate, typename... Args>
    constexpr auto move_template_types(SrcTemplate<Args...> &&) -> DestTemplate<Args...>;    

    template <template <typename...> typename DestTemplate, typename SrcTemplate, bool IS_TEMPLATE = IS_TEMPLATE<SrcTemplate>>
    struct MoveTemplateTypesImpl 
    {
        using Result = void;
    };

    template <template <typename...> typename DestTemplate, typename SrcTemplate>
    struct MoveTemplateTypesImpl<DestTemplate, SrcTemplate, true>
    {
        using Result = decltype(move_template_types<DestTemplate>(std::declval<SrcTemplate>()));
    };

#ifndef _MSC_VER
    template <template <typename...> typename DestTemplate, typename SrcTemplate>
    using MoveTemplateTypes = typename MoveTemplateTypesImpl<DestTemplate, SrcTemplate>::Result;

#else
    template 
    <
        template <typename...> typename TemplateType,
        typename Tuple, 
        bool ENOUGH,
        size_t INDEX,
        size_t TYPES_COUNT,
        typename... Types
    >
    struct MoveStdTupleTypesProxy : MoveStdTupleTypesProxy
    <
        TemplateType, 
        Tuple, 
        TYPES_COUNT == INDEX + 1,
        INDEX + 1,
        TYPES_COUNT,
        Types...,
        typename std::tuple_element<INDEX, Tuple>::type
    >
    {
    };

    template
    <
        template <typename...> typename TemplateType,
        typename Tuple,
        size_t INDEX,
        size_t TYPES_COUNT,
        typename... Types
    >
    struct MoveStdTupleTypesProxy<TemplateType, Tuple, true, INDEX, TYPES_COUNT, Types...>
    {
        using ResultType = TemplateType<Types...>;
    };

    template <template <typename...> typename TemplateType, typename Tuple>
    struct MoveStdTupleTypes
    {
        using ResultType = typename MoveStdTupleTypesProxy
            <
                TemplateType, 
                Tuple, 
                std::tuple_size<Tuple>::value == 1,
                1,
                std::tuple_size<Tuple>::value,
                typename std::tuple_element<0, Tuple>::type
            >::ResultType;
    };

    template <template <typename...> typename TemplateType>
    struct MoveStdTupleTypes<TemplateType, std::tuple<>>
    {
        using ResultType = TemplateType<>;
    };

    template <template <typename...> typename DestTemplate, typename SrcTemplate>
    using MoveTemplateTypes = typename MoveStdTupleTypes<DestTemplate, typename MoveTemplateTypesImpl<std::tuple, SrcTemplate>::Result>::ResultType;

#endif // _MSC_VER
}

#endif // METAXXA_MOVETEMPLATETYPES_H