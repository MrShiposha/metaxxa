#ifndef METAXXA_MOVETEMPLATETYPESUNIQUE_H
#define METAXXA_MOVETEMPLATETYPESUNIQUE_H

#include <tuple>

#include "MoveTemplateTypes.h"
#include "../DistinctOfStdTuple.h"
#include "IsTemplate.h"

namespace metaxxa::detail
{
    template <template <typename...> typename TemplateType, typename Type, bool IS_TYPE_TEMPLATE = is_template<Type>()>
    struct MoveTemplateTypesImpl
    {};

    template <template <typename...> typename TemplateType, typename Type>
    struct MoveTemplateTypesImpl<TemplateType, Type, true>
    {
        using Result = detail::MoveTemplateTypes<TemplateType, decltype(::metaxxa::distinct_types<detail::MoveTemplateTypes<std::tuple, Type>>())>;
    };

    template <template <typename...> typename TemplateType, typename Type>
	using MoveTemplateTypesUnique = typename MoveTemplateTypesImpl<TemplateType, Type>::Result;
}

#endif // METAXXA_MOVETEMPLATETYPESUNIQUE_H