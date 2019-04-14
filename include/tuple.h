#ifndef METAXXA_TUPLE_H
#define METAXXA_TUPLE_H

#include <utility>

#include "typetuple.h"
#include "def.h"

namespace metaxxa
{
    template <typename... Types>
    class Tuple : TypeTuple<Types...>
    {
    public:
        using TypeTuple = metaxxa::TypeTuple<Types...>;

        Tuple();

        Tuple(Types&&... args);

        ~Tuple();

        template <std::size_t INDEX>
        metaxxa_inline auto &get();

        template <std::size_t INDEX>
        metaxxa_inline const auto &get() const;

        template <typename T>
        metaxxa_inline auto &get(std::size_t index);

        template <typename T>
        metaxxa_inline const auto &get(std::size_t index) const;

        metaxxa_inline void *get(std::size_t index);

        metaxxa_inline const void *get(std::size_t index) const;

    private:
        template <std::size_t... INDICES>
        metaxxa_inline void construct(std::index_sequence<INDICES...>);

        template <std::size_t... INDICES>
        metaxxa_inline void construct(Types&&... args, std::index_sequence<INDICES...>);

        template <std::size_t... INDICES>
        metaxxa_inline void deallocate(std::index_sequence<INDICES...>);

        template <std::size_t INDEX, typename T>
        metaxxa_inline void deallocate();

        unsigned char *data;
        std::size_t    offsets[TypeTuple::size()];
    };
}

#endif // METAXXA_TUPLE_H