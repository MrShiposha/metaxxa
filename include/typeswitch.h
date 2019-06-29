#ifndef METAXXA_TYPESWITCH_H
#define METAXXA_TYPESWITCH_H

#include <type_traits>

namespace metaxxa
{
    template <typename CaseCondition, typename CaseType>
    struct TypeSwitchCase
    {
        using Condition = CaseCondition;
        using type      = CaseType;

        template <typename T>
        static constexpr bool is_equal_to() { return std::is_same_v<T, Condition>; }
    };

    template <typename CaseType>
    struct TypeSwitchDefaultCase
    {
        using type = CaseType;

        template <typename T>
        static constexpr bool is_equal_to() { return true; }
    };

    namespace detail
    {
        template <typename CaseCondition, typename CasesList>
        struct TypeSwitchType
        {
            template <typename TypeSwitchCase>
            struct Functor
            {
                static constexpr bool value = TypeSwitchCase::template is_equal_to<CaseCondition>();
            };

            using Type = typename Find<CasesList, Functor>::Type::type;
        };

        template <typename DefaultType, typename CasesList>
        struct TypeSwitchDefault
        {
            using Cases = Concat<TypeList, CasesList, TemplateContainer<TypeSwitchDefaultCase<DefaultType>>>;

            template <typename T>
            using Type = typename TypeSwitchType<T, Cases>::Type;
        };

        template <typename CaseCondition, typename CaseType, typename CasesList>
        struct TypeCaseImpl
        {
            using Cases = Concat<TypeList, CasesList, TemplateContainer<TypeSwitchCase<CaseCondition, CaseType>>>;

            template <typename NextCaseCondition, typename NextCaseType>
            using Case = TypeCaseImpl<NextCaseCondition, NextCaseType, Cases>;

            template <typename DefaultT>
            using Default = TypeSwitchDefault<DefaultT, Cases>; 

            template <typename T>
            using Type = typename TypeSwitchType<T, Cases>::Type;
        };
    }

    struct TypeSwitch
    {
        template <typename CaseCondition, typename CaseType>
        using Case = detail::TypeCaseImpl
        <
            CaseCondition,
            CaseType,
            TypeList<>
        >;
    };
}

#endif // METAXXA_TYPESWITCH_H