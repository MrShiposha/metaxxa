#ifndef METAXXA_CONCAT_H
#define METAXXA_CONCAT_H

#include "typelist.h"
#include "moveparameters.h"

namespace metaxxa
{
    namespace detail
    {
        template
        <
            template <typename...> typename Template,
            typename RHS,
            typename... LHSArgs
        >
        struct Concatenator
        {
            template <typename... RHSArgs>
            static constexpr auto evaltype(TypeList<RHSArgs...> &&)
                -> Template<LHSArgs..., RHSArgs...>;

            using RHSTypeList = MoveParameters<TypeList, RHS>;
            using Type = decltype(evaltype(std::declval<RHSTypeList>()));
        };

        template
        <
            template <typename...> typename Template,
            typename LHS,
            typename RHS
        >
        struct ConcatenatorFacade 
        {
            template <typename... LHSArgs>
            static constexpr auto evaltype(TypeList<LHSArgs...> &&)
                -> Concatenator<Template, RHS, LHSArgs...>;

            using LHSTypeList = MoveParameters<TypeList, LHS>;
            using Type = typename decltype(evaltype(std::declval<LHSTypeList>()))::Type;
        };
    }

    template
    <
        template <typename...> typename Template,
        typename LHS,
        typename RHS
    >
    using Concat = typename detail::ConcatenatorFacade<Template, LHS, RHS>::Type;
}

#endif // METAXXA_CONCAT_H