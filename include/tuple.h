#ifndef METAXXA_TUPLE_H
#define METAXXA_TUPLE_H

#include <utility>

#include "typetuple.h"
#include "moveparameters.h"
#include "def.h"

namespace metaxxa
{
    template <typename... Types>
    class Tuple : public TypeTuple<Types...>
    {
    public:
        using TypeTuple = metaxxa::TypeTuple<Types...>;

        Tuple();

        Tuple(Types&&... args);

        Tuple(const Types&... args);

        template <typename TupleT>
        Tuple(const TupleT &);

        Tuple(const Tuple &);

        Tuple(Tuple &&);

        ~Tuple();

        template <typename TupleT>
        Tuple &operator=(const TupleT &);

        Tuple &operator=(const Tuple &);

        Tuple &operator=(Tuple &&);

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
        metaxxa_inline void construct(const Types&... args, std::index_sequence<INDICES...>);

        template <typename OtherTuple, std::size_t... INDICES>
        metaxxa_inline void construct(const OtherTuple &other, std::index_sequence<INDICES...>);

        template <std::size_t... INDICES>
        metaxxa_inline void deallocate(std::index_sequence<INDICES...>);

        template <std::size_t INDEX, typename T>
        metaxxa_inline void deallocate();

        unsigned char *data;
        std::size_t    offsets[TypeTuple::size()];
    };

    template <typename TupleT>
    using TupleFrom = MoveParameters<Tuple, TupleT>;
}

namespace std
{
    template <std::size_t INDEX, typename... Args>
    class tuple_element<INDEX, metaxxa::Tuple<Args...>>
    {
    public:
        using type = std::tuple_element_t<INDEX, typename metaxxa::Tuple<Args...>::TypeTuple>;
    };

    template <typename... Args>
    class tuple_size<metaxxa::Tuple<Args...>>
    {
    public:
        static constexpr std::size_t value = std::tuple_size_v<typename metaxxa::Tuple<Args...>::TypeTuple>;
    };

    template <std::size_t INDEX, typename... Args>
    auto &get(metaxxa::Tuple<Args...> &);

    template <std::size_t INDEX, typename... Args>
    auto &get(const metaxxa::Tuple<Args...> &);

    template <typename Callable, typename... Args>
    constexpr auto apply(Callable &&, metaxxa::Tuple<Args...> &&);
}

#endif // METAXXA_TUPLE_H