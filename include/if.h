#ifndef METAXXA_IF_H
#define METAXXA_IF_H

#include "typesaver.h"

namespace metaxxa
{
    namespace detail
    {
        template <bool CONDITION, typename Then, typename Else>
        struct ElseResolver
        {
            using Type = Then;
        };

        template <typename Then, typename Else>
        struct ElseResolver<false, Then, Else>
        {
            using Type = Else;
        };

        template <bool CONDITION, typename T>
        struct ThenResolver
        {
            template <typename E>
            using Else = ElseResolver<CONDITION, T, E>;
        };

        template <typename T>
        struct ThenResolver<true, T>
        {
            using Type = T;

            template <typename E>
            using Else = ElseResolver<true, T, E>;
        };
    }

    template <bool CONDITION>
    struct If
    {
        template <typename T>
        using Then = detail::ThenResolver<CONDITION, T>;
    };
}

#endif // METAXXA_IF_H