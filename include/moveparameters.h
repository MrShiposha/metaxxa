#ifndef METAXXA_MOVEPARAMETERS_H
#define METAXXA_MOVEPARAMETERS_H

#include "typesaver.h"

namespace metaxxa
{
    namespace detail
    {
        template <typename... StartTypes>
        struct Mover
        {
            template
            <
                template <typename...> typename DestTemplate,
                template <typename...> typename SrcTemplate,
                typename... Args
            >
            static constexpr auto move_parameters(SrcTemplate<Args...> &&) -> TypeSaver<DestTemplate<StartTypes..., Args...>>;
        };
    }

    template 
    <
        template <typename...> typename DestTemplate,
        typename SrcTemplate,
        typename... StartTypes
    >
    using MoveParameters = typename decltype
    (
        detail::Mover<StartTypes...>::move_parameters<DestTemplate>(std::declval<SrcTemplate>())
    )::Type;
}

#endif // METAXXA_MOVEPARAMETERS_H