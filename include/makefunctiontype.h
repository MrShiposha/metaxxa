#ifndef METAXXA_MAKEFUNCTIONTYPE_H
#define METAXXA_MAKEFUNCTIONTYPE_H

#include <type_traits>

#include "algorithm/skiprange.h"
#include "typelist.h"

namespace metaxxa
{
    namespace detail
    {
        template <typename ResultType>
        struct MakeFunctionType
        {
            template <typename... Args>
            using Type = ResultType(Args...);
        };

        template <typename Tuple, std::size_t RETURN_INDEX>
        struct MakeFunctionTypeImpl
        {
            using ResultType = std::tuple_element_t<RETURN_INDEX, Tuple>;
            // using ArgsTuple  = TakeRange<TypeList, Tuple, >;
        };
    }
}

#endif // METAXXA_MAKEFUNCTIONTYPE_H