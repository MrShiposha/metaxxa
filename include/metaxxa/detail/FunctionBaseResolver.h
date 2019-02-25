#ifndef METAXXA_detail_FUNCTIONBASERESOLVER_H
#define METAXXA_detail_FUNCTIONBASERESOLVER_H

#include "../NonFunctionTag.h"

namespace metaxxa::detail
{
    template <typename T>
    struct CallOperatorTester
    {
        template <typename U>
        struct helper {};

        template <typename U>
        static constexpr uint8_t check(helper<decltype(&U::operator())> *);

        template <typename U>
        static constexpr uint16_t check(...);

        static constexpr bool HAS = (sizeof(check<T>(0)) == sizeof(uint8_t));
    };

    template 
    <
        typename T, 
        template <typename> typename Function, 
        bool HAS_CALL_OPERATOR = CallOperatorTester<T>::HAS
    >
    struct FunctionBaseResolver
    {};

    template 
    <
        typename T, 
        template <typename> typename Function
    >
    struct FunctionBaseResolver<T, Function, true>
    {
        using Base = Function<decltype(&T::operator())>;
    };

    template 
    <
        typename T, 
        template <typename> typename Function
    >
    struct FunctionBaseResolver<T, Function, false>
    {
        using Base = NonFunctionTag;
    };
}

#endif // METAXXA_detail_FUNCTIONBASERESOLVER_H