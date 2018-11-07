#ifndef METAXXA_ISCLASSTEMPLATE_H
#define METAXXA_ISCLASSTEMPLATE_H

namespace metaxxa::detail
{
    template <typename Type>
    struct IsTemplate
    {
        template <template <typename...> typename TemplateType, typename... Args>
        static int16_t check(TemplateType<Args...>);

        static int8_t check(...);

        static constexpr bool RESULT = sizeof(int16_t) == sizeof(check(std::declval<Type>()));
    };

    template <>
    struct IsTemplate<void>
    {
        static constexpr bool RESULT = false;
    };

    template <typename Type>
    constexpr bool IS_TEMPLATE = IsTemplate<Type>::RESULT; 
}

#endif // METAXXA_ISCLASSTEMPLATE_H