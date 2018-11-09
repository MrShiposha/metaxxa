#ifndef METAXXA_OPTIONAL_H
#define METAXXA_OPTIONAL_H

#if __has_include(<optional>)
    #include <optional>

    #define ___METAXXA___OPTIONAL std::optional
    

#elif __has_include(<experimental/optional>)
    #include <experimental/optional>

    #define ___METAXXA___OPTIONAL std::experimental::optional
#else
    #error METAXXA: Sorry, your compiler does not support neither std::optional or std::experimental::optional
#endif // Check optional

#endif // METAXXA_OPTIONAL_H