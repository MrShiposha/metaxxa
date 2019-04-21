#ifndef METAXXA_ISINSTANTIATIONOF_H
#define METAXXA_ISINSTANTIATIONOF_H

#include <type_traits>

namespace metaxxa
{
    namespace detail
    {
        template
        <
            template <typename...> typename TupleT,
            template <typename...> typename Template,
            typename... Args
        >
        constexpr auto is_instatiation_of(Template<Args...>&&)
            -> std::integral_constant<bool, std::is_same_v<TupleT<Args...>, Template<Args...>>>;
        
        template <template <typename...> typename TupleT>
        constexpr auto is_instatiation_of(...)
            -> std::false_type;


        template
        <
            typename ArgsT,
            template <typename U, U...> typename TupleT,
            template <typename U, U...> typename Template,
            ArgsT... Args
        >
        constexpr auto is_instatiation_of(Template<ArgsT, Args...>&&)
            -> std::integral_constant
            <
                bool, 
                std::is_same_v
                <
                    TupleT<ArgsT, Args...>, 
                    Template<ArgsT, Args...>
                >
            >;
        
        template 
        <
            typename ArgsT,        
            template <typename U, U...> typename TupleT
        >
        constexpr auto is_instatiation_of(...)
            -> std::false_type;
    }

    template
    <
        template <typename...> typename Template,
        typename T
    >
    constexpr bool is_instatiation_of()
    {
        return std::is_same_v
        <
            std::true_type, 
            decltype(detail::is_instatiation_of<Template>(std::declval<T>()))
        >;
    }

    template
    <
        typename ArgsT,
        template <typename U, U...> typename Template,
        typename T
    >
    constexpr bool is_instatiation_of()
    {
        return std::is_same_v
        <
            std::true_type, 
            decltype
            (
                detail::is_instatiation_of
                <
                    ArgsT,
                    Template
                >(std::declval<T>())
            )
        >;
    }
}

#endif // METAXXA_ISINSTANTIATIONOF_H