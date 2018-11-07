#ifndef METAXXA_MOVETEMPLATETYPESUNIQUE_H
#define METAXXA_MOVETEMPLATETYPESUNIQUE_H

#include <tuple>

#include "MoveTemplateTypes.h"
#include "../DistinctOfStdTuple.h"
#include "IsTemplate.h"

namespace metaxxa::detail
{
    template <template <typename...> typename TemplateType, typename Type, bool IS_TYPE_TEMPLATE = IS_TEMPLATE<Type>>
    struct MoveTemplateTypesUniqueImpl
    {};

    template <template <typename...> typename TemplateType, typename Type>
    struct MoveTemplateTypesUniqueImpl<TemplateType, Type, true>
    {
        using Result = detail::MoveTemplateTypes<TemplateType, decltype(::metaxxa::distinct_types<detail::MoveTemplateTypes<std::tuple, Type>>())>;
    };

    template <template <typename...> typename TemplateType, typename Type>
	using MoveTemplateTypesUnique = typename MoveTemplateTypesUniqueImpl<TemplateType, Type>::Result;
}

#endif // METAXXA_MOVETEMPLATETYPESUNIQUE_H