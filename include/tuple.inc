#ifndef METAXXA_TUPLE_INC
#define METAXXA_TUPLE_INC

#include "tuple.h"
#include "indexrange.h"
#include "algorithm/takefirst.h"

namespace metaxxa
{
    namespace detail
    {
        template <typename... Args>
        constexpr std::size_t memory_size()
        {
            return (0 + ... + sizeof(Args));
        }

        template <template <typename...> typename Tuple, typename... Args>
        constexpr std::size_t memory_size(Tuple<Args...> &&)
        {
            return memory_size<Args...>();
        }
    }

    template <typename... Args>
    Tuple<Args...>::Tuple()
    : data(static_cast<unsigned char *>(malloc(detail::memory_size<Args...>())))
    {
        construct(std::make_index_sequence<TypeTuple::size()>());
    }

    template <typename... Args>
    Tuple<Args...>::Tuple(Args&&... args)
    : data(static_cast<unsigned char *>(malloc(detail::memory_size<Args...>())))
    {
        construct(std::forward<Args>(args)..., std::make_index_sequence<TypeTuple::size()>());
    }

    template <typename... Args>
    Tuple<Args...>::~Tuple()
    {
        deallocate(MakeReverseIndexRange<TypeTuple::size(), 0>());
    }

    template <typename... Args>
    metaxxa_inline void *Tuple<Args...>::get(std::size_t index)
    {
        return static_cast<void *>(data + offsets[index]);
    }

    template <typename... Args>
    metaxxa_inline const void *Tuple<Args...>::get(std::size_t index) const
    {
        return const_cast<Tuple<Args...>*>(this)->get(index);
    }

    template <typename... Args>
    template <typename T>
    metaxxa_inline auto &Tuple<Args...>::get(std::size_t index)
    {
        return *static_cast<T*>(get(index));
    }

    template <typename... Args>
    template <typename T>
    metaxxa_inline const auto &Tuple<Args...>::get(std::size_t index) const
    {
        return const_cast<Tuple<Args...>*>(this)->template get<T>(index);
    }

    template <typename... Args>
    template <std::size_t INDEX>
    metaxxa_inline auto &Tuple<Args...>::get()
    {
        return get<typename TypeTuple::template Get<INDEX>>(INDEX);
    }

    template <typename... Args>
    template <std::size_t INDEX>
    metaxxa_inline const auto &Tuple<Args...>::get() const
    {
        return const_cast<Tuple<Args...>*>(this)->template get<INDEX>();
    }

    template <typename... Args>
    template <std::size_t... INDICES>
    metaxxa_inline void Tuple<Args...>::construct(std::index_sequence<INDICES...>)
    {
        ((void)(offsets[INDICES] = detail::memory_size(TakeFirst<TypeList, TypeTuple, INDICES>())), ...);

        if(data)
            ((void)(new (get(INDICES)) typename TypeTuple::template Get<INDICES>()), ...);
    }

    template <typename... Args>
    template <std::size_t... INDICES>
    metaxxa_inline void Tuple<Args...>::construct(Args&&... args, std::index_sequence<INDICES...>)
    {
        ((void)(offsets[INDICES] = detail::memory_size(TakeFirst<TypeList, TypeTuple, INDICES>())), ...);

        if(data)
            ((void)(new (get(INDICES)) typename TypeTuple::template Get<INDICES>(args)), ...);
    }

    template <typename... Args>
    template <std::size_t... INDICES>
    metaxxa_inline void Tuple<Args...>::deallocate(std::index_sequence<INDICES...>)
    {
        if(data)
        {
            (deallocate<INDICES, typename TypeTuple::template Get<INDICES>>(), ...);
            ::free(data);
        }
    }

    template <typename... Args>
    template <std::size_t INDEX, typename T>
    metaxxa_inline void Tuple<Args...>::deallocate()
    {
        get<INDEX>().~T();
    }
}

namespace std
{
    template <std::size_t INDEX, typename... Args>
    auto &get(metaxxa::Tuple<Args...> &tuple)
    {
        return tuple.template get<INDEX>();
    }

    template <std::size_t INDEX, typename... Args>
    auto &get(const metaxxa::Tuple<Args...> &tuple)
    {
        return tuple.template get<INDEX>();
    }
}

#endif // METAXXA_TUPLE_INC