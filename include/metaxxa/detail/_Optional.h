#ifndef METAXXA_OPTIONAL_H
#define METAXXA_OPTIONAL_H

#if __has_include(<optional>)
    #include <optional>

    #define METAXXA_OPTIONAL std::optional
    

#elif __has_include(<experimental/optional>)
    #include <experimental/optional>

    #define METAXXA_OPTIONAL std::experimental::optional
#else
    #error METAXXA: Sorry, your compiler does not support neither std::optional or std::experimental::optional
#endif // Check optional

#endif // METAXXA_OPTIONAL_H