#ifndef METAXXA_TUPLE_H
#define METAXXA_TUPLE_H

#include <utility>

#include "typetuple.h"
#include "def.h"

namespace metaxxa
{
    enum ReconstructPolicy
    {
        DestructBeforeConstruct = 0,
        ReconstructOnly
    };

    template <typename... Types>
    class Tuple : public TypeTuple<Types...>
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

        template 
        <
            std::size_t INDEX, 
            ReconstructPolicy POLICY = DestructBeforeConstruct, 
            typename... Args
        >
        metaxxa_inline void reconstruct(Args&&... args);

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
}

#endif // METAXXA_TUPLE_H