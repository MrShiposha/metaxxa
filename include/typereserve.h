#ifndef METAXXA_TYPERESERVE_H
#define METAXXA_TYPERESERVE_H

#include <cstddef>
#include <cstdint>

template <typename T, std::size_t TN>
struct TypeReserve 
{
    using Type = T;
    static constexpr std::size_t AMOUNT = TN;
};

#endif // METAXXA_TYPERESERVE_H