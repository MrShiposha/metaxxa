#ifndef METAXXA_detail_FUNCTIONBASERESOLVER_H
#define METAXXA_detail_FUNCTIONBASERESOLVER_H

#include "OperatorTesters.h"
#include "../NonFunctionTag.h"

namespace metaxxa::detail
{
    template 
    <
        typename T, 
        template <typename> typename Function, 
        bool HAS_CALL_OPERATOR = ___METAXXA___OPERATOR_TESTER_call<T, void>::has()
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