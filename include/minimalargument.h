#ifndef METAXXA_MINIMALARGUMENT_H
#define METAXXA_MINIMALARGUMENT_H

#include "typeif.h"

namespace metaxxa
{
    template <typename T>
    using MinimalArgument = typename 
        TypeIf<sizeof(T) <= sizeof(T *)>
                ::template Then<T>
                ::template Else<const T &>
                ::Type;
}

#endif // METAXXA_MINIMALARGUMENT_H