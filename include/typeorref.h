#ifndef METAXXA_TYPEORREF_H
#define METAXXA_TYPEORREF_H

#include "if.h"

namespace metaxxa
{
    template <typename T>
    using TypeOrRef = typename 
        If<sizeof(T) <= sizeof(T *)>
                ::template Then<T>
                ::template Else<const T &>
                ::Type;
}

#endif // METAXXA_TYPEORREF_H