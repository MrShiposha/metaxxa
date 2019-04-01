#ifndef METAXXA_MINIMALTYPE_H
#define METAXXA_MINIMALTYPE_H

#include "typeif.h"

namespace metaxxa
{
    template <typename T>
    using MinimalType = typename 
        TypeIf<sizeof(T) <= sizeof(T *)>
                ::template Then<T>
                ::template Else<const T &>
                ::Type;
}

#endif // METAXXA_MINIMALTYPE_H