#ifndef METAXXA_MINIMALARGUMENT_H
#define METAXXA_MINIMALARGUMENT_H

#include "if.h"

namespace metaxxa
{
    template <typename T>
    using MinimalArgument = typename 
        If<sizeof(T) <= sizeof(T *)>
                ::template Then<T>
                ::template Else<const T &>
                ::Type;
}

#endif // METAXXA_MINIMALARGUMENT_H