#ifndef METAXXA_VARIANT_H
#define METAXXA_VARIANT_H

#if __has_include(<variant>)
    #include <variant>

    #define ___METAXXA___VARIANT std::variant
#elif __has_include(<experimental/variant>)
    #include <experimental/variant>

    #define ___METAXXA___VARIANT std::experimental::variant
#else
    #error METAXXA: Sorry, your compiler does not support neither std::variant or std::experimental::variant
#endif // Check variant

#endif // METAXXA_VARIANT_H