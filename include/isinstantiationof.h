#ifndef METAXXA_ISINSTANTIATIONOF_H
#define METAXXA_ISINSTANTIATIONOF_H

#include <type_traits>

namespace metaxxa
{
    namespace detail
    {
        template 
        <
            template <typename...> typename TemplateType, 
            template <typename...> typename SrcType, 
            typename... Types
        >
        constexpr auto is_instatiation_of(SrcType<Types...> &&)
            -> std::bool_constant<std::is_same_v<TemplateType<Types...>, SrcType<Types...>>>;

        template 
        <
            template <typename...> typename TemplateType,
            typename SrcType,
            typename... Types
        >
        constexpr auto is_instatiation_of(SrcType &&)
            -> std::false_type;
    }

    template <typename T, template <typename...> typename TemplateType>
    constexpr bool is_instatiation_of()
    {
        return decltype(detail::is_instatiation_of<TemplateType>(std::declval<T>()))::value;
    }
}

#endif // METAXXA_ISINSTANTIATIONOF_H