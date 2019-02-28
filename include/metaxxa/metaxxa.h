#ifndef METAXXA_H
#define METAXXA_H

#if defined(_MSC_VER)
    #define METAXXA_TEMPLATE
#elif defined(__clang__)
    #define METAXXA_TEMPLATE template
#elif defined(__GNUC__)
    #define METAXXA_TEMPLATE template
#else
    #ifndef METAXXA_TEMPLATE
        #error METAXXA: You are using an unknown compiler. Please specify the METAXXA_TEMPLATE macro
    #endif // METAXXA_TEMPLATE
#endif // Compilers

#include "Tuple.inc"
#include "Type.inc"
#include "Function.inc"
#include "MoveFunctionArgumentTypes.h"

#endif // METAXXA_H