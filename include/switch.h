#ifndef METAXXA_SWITCH_H
#define METAXXA_SWITCH_H

#include "typelist.h"
#include "literal.h"
#include "algorithm/concat.h"
#include "algorithm/find.h" 
#include "if.h"

namespace metaxxa
{
    template <typename T, T CONSTANT, typename CaseType>
    struct SwitchCase
    {
        using ConstantType = T;
        static constexpr ConstantType value = CONSTANT;

        using type = CaseType;

        template <T VALUE>
        static constexpr bool is_equal_to() { return value == VALUE; }
    };

    template <typename T, typename CaseType>
    struct SwitchDefaultCase
    {
        using type = CaseType;

        template <T VALUE>
        static constexpr bool is_equal_to() { return true; }
    };

    namespace detail
    {
        template <typename T, T CONSTANT, typename Cases>
        struct SwitchType
        {
            template <typename SwitchCase>
            struct Functor
            {
                static constexpr bool value = SwitchCase::template is_equal_to<CONSTANT>();
            };

            using Type = typename Find<Cases, Functor>::Type::type;
        };

        template <typename T, typename DefaultType, typename CasesList>
        struct SwitchDefault
        {
            using Cases = Concat<TypeList, CasesList, TemplateContainer<SwitchDefaultCase<T, DefaultType>>>;

            template <T CONSTANT>
            using Type = typename SwitchType<T, CONSTANT, Cases>::Type;
        };

        template <typename T, T CASE_CONSTANT, typename CaseType, typename CasesList>
        struct CaseImpl
        {
            using Cases = Concat<TypeList, CasesList, TemplateContainer<SwitchCase<T, CASE_CONSTANT, CaseType>>>;

            template <T NEXT_CONSTANT, typename NextCaseType>
            using Case = CaseImpl<T, NEXT_CONSTANT, NextCaseType, Cases>;

            template <typename DefaultT>
            using Default = SwitchDefault<T, DefaultT, Cases>; 

            template <T CONSTANT>
            using Type = typename SwitchType<T, CONSTANT, Cases>::Type;
        };
    }

    template <typename T>
    struct Switch
    {
        template <T CASE_CONSTANT, typename CaseType>
        using Case = detail::CaseImpl
        <
            T,
            CASE_CONSTANT,
            CaseType,
            TypeList<>
        >;
    };
}

#endif // METAXXA_SWITCH_H