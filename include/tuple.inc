#ifndef METAXXA_TUPLE_INC
#define METAXXA_TUPLE_INC

#include <cstring>

#include "tuple.h"
#include "indexrange.h"
#include "algorithm/takefirst.h"
#include "algorithm/takerange.h"

#define ALLOCATE_DATA() \
    data                                                                                                    \
    (                                                                                                       \
        static_cast<unsigned char *>(malloc(detail::memory_size<Args...>())),                               \
        [this](unsigned char *addr) { deallocate(addr, MakeReverseIndexRange<size(), 0>()); }               \
    ),                                                                                                      \
    memory_size(detail::memory_size<Args...>())

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
    : ALLOCATE_DATA()
    {
        construct(std::make_index_sequence<size()>());
    }

    template <typename... Args>
    Tuple<Args...>::Tuple(Args&&... args)
    : ALLOCATE_DATA()
    {
        construct(std::forward<Args>(args)..., std::make_index_sequence<size()>());
    }

    template <typename... Args>
    Tuple<Args...>::Tuple(const Args&... args)
    : ALLOCATE_DATA()
    {
        construct(args..., std::make_index_sequence<size()>());
    }

    template <typename... Args>
    template <typename TupleT>
    Tuple<Args...>::Tuple(const TupleT &other)
    : ALLOCATE_DATA()
    {
        construct(other, std::make_index_sequence<std::tuple_size_v<TupleT>>());
    }

    template <typename... Args>
    Tuple<Args...>::Tuple(const Tuple &other)
    : ALLOCATE_DATA()
    {
        construct(other, std::make_index_sequence<size()>());
    }

    template <typename... Args>
    Tuple<Args...>::Tuple(Tuple &&other)
    : data(other.data), memory_size(other.memory_size)
    {
        other.data = nullptr;
        for(std::size_t i = 0; i < size(); ++i)
            offsets[i] = other.offsets[i];
    }

    template <typename... Args>
    Tuple<Args...>::Tuple(detail::NotTupleElement, std::shared_ptr<unsigned char> data, std::size_t memory_size, std::size_t offset)
    : data(data), memory_size(memory_size)
    {
        init_offsets(offset, std::make_index_sequence<TypeTuple::size()>());
    }

    template <typename... Args>
    Tuple<Args...>::~Tuple()
    {}

    template <typename... Args>
    template <typename TupleT>
    Tuple<Args...> &Tuple<Args...>::operator=(const TupleT &rhs)
    {
        return *this = std::move(Tuple(rhs));
    }

    template <typename... Args>
    Tuple<Args...> &Tuple<Args...>::operator=(const Tuple &rhs)
    {
        if(this != &rhs)
            *this = std::move(Tuple(rhs));

        return *this;
    }

    template <typename... Args>
    Tuple<Args...> &Tuple<Args...>::operator=(Tuple &&rhs)
    {
        data = rhs.data;
        rhs.data = nullptr;
        return *this;
    }

    template <typename... Args>
    metaxxa_inline void *Tuple<Args...>::get(std::size_t index)
    {
        return static_cast<void *>(data.get() + offsets[index]);
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
    metaxxa_inline std::size_t Tuple<Args...>::capacity() const
    {
        return memory_size;
    }

    template <typename... Args>
    metaxxa_inline void Tuple<Args...>::shrink_to_fit()
    {
        reallocate(detail::memory_size<Args...>());
    }

    // template <typename... Args>
    // template <typename TupleRHS>
    // metaxxa_inline auto Tuple<Args...>::concat(const TupleRHS &rhs) const
    // {
    //     using ResultTuple = Concat<::metaxxa::Tuple, Tuple, TupleRHS>;
    //     return ResultTuple();
    // }

    // template <typename... Args>
    // template <typename TupleRHS>
    // metaxxa_inline auto Tuple<Args...>::concat_shared(const TupleRHS &rhs) const
    // {

    // }

    // template <typename... Args>
    // template <typename TupleRHS>
    // metaxxa_inline auto Tuple<Args...>::concat_shared_greedy(const TupleRHS &rhs) const
    // {

    // }

    template <typename... Args>
    template <std::size_t... INDICES>
    metaxxa_inline auto Tuple<Args...>::only_indices(std::index_sequence<INDICES...>) const
    {
        return only_indices<INDICES...>();
    }

#   ifdef _MSC_VER
    template <typename... Args>
    template <std::size_t... INDICES>
    metaxxa_inline auto Tuple<Args...>::only_indices() const
    {
        return Tuple<std::tuple_element_t<INDICES, Tuple>...>(get<INDICES>()...);
    }
#   endif // _MSC_VER


    template <typename... Args>
    template <std::size_t FROM, std::size_t TO>
    metaxxa_inline auto Tuple<Args...>::take_range() const
    {
        return only_indices(MakeIndexRange<FROM, TO>());
    }

    template <typename... Args>
    template <std::size_t FROM, std::size_t TO>
    metaxxa_inline auto Tuple<Args...>::take_range_shared() const
    {
        using ResultTuple = TakeRange<::metaxxa::Tuple, Tuple, FROM, TO>;
        return ResultTuple(detail::NotTupleElement{}, data, memory_size, offsets[FROM]);
    }

    template <typename... Args>
    template <std::size_t N>
    metaxxa_inline auto Tuple<Args...>::take_first() const
    {
        return take_range<0, N>();
    }

    template <typename... Args>
    template <std::size_t N>
    metaxxa_inline auto Tuple<Args...>::take_first_shared() const
    {
        return take_range_shared<0, N>();
    }

    template <typename... Args>
    template <std::size_t N>
    metaxxa_inline auto Tuple<Args...>::take_last() const
    {
        return take_range<size() - N, size()>();
    }

    template <typename... Args>
    template <std::size_t N>
    metaxxa_inline auto Tuple<Args...>::take_last_shared() const
    {
        return take_range_shared<size() - N, size()>();
    }

    template <typename... Args>
    template <std::size_t N>
    metaxxa_inline auto Tuple<Args...>::skip_first() const
    {
        return take_range<N, size()>();
    }

    template <typename... Args>
    template <std::size_t N>
    metaxxa_inline auto Tuple<Args...>::skip_first_shared() const
    {
        return take_range_shared<N, size()>();
    }

    template <typename... Args>
    template <std::size_t N>
    metaxxa_inline auto Tuple<Args...>::skip_last() const
    {
        return take_range<0, size() - N>();
    }

    template <typename... Args>
    template <std::size_t N>
    metaxxa_inline auto Tuple<Args...>::skip_last_shared() const
    {
        return take_range_shared<0, size() - N>();
    }

    template <typename... Args>
    metaxxa_inline void Tuple<Args...>::reallocate(std::size_t new_memory_size)
    {
        if(new_memory_size != memory_size)
        {
            auto *new_data = static_cast<unsigned char *>(malloc(new_memory_size));
            std::memcpy(new_data, data.get(), std::min(new_memory_size, memory_size));
            data.reset(new_data);   

            memory_size = new_memory_size;
        }
    }

    template <typename... Args>
    template <std::size_t... INDICES>
    metaxxa_inline void Tuple<Args...>::init_offsets(std::size_t start, std::index_sequence<INDICES...>)
    {
        ((void)(offsets[INDICES] = start + detail::memory_size(TakeFirst<TypeList, TypeTuple, INDICES>())), ...);
    }

    template <typename... Args>
    template <std::size_t... INDICES>
    metaxxa_inline void Tuple<Args...>::construct(std::index_sequence<INDICES...> seq)
    {
        init_offsets(0, seq);

        if(data)
            ((void)(new (get(INDICES)) typename TypeTuple::template Get<INDICES>()), ...);
    }

    template <typename... Args>
    template <std::size_t... INDICES>
    metaxxa_inline void Tuple<Args...>::construct(Args&&... args, std::index_sequence<INDICES...> seq)
    {
        init_offsets(0, seq);

        if(data)
            ((void)(new (get(INDICES)) typename TypeTuple::template Get<INDICES>(std::forward<Args>(args))), ...);
    }

    template <typename... Args>
    template <std::size_t... INDICES>
    metaxxa_inline void Tuple<Args...>::construct(const Args&... args, std::index_sequence<INDICES...> seq)
    {
        init_offsets(0, seq);

        if(data)
            ((void)(new (get(INDICES)) typename TypeTuple::template Get<INDICES>(args)), ...);
    }

    template <typename... Args>
    template <typename OtherTuple, std::size_t... INDICES>
    metaxxa_inline void Tuple<Args...>::construct(const OtherTuple &other, std::index_sequence<INDICES...> seq)
    {
        init_offsets(0, seq);

        if(data)
            ((void)(new (get(INDICES)) typename TypeTuple::template Get<INDICES>(std::get<INDICES>(other))), ...);
    }

    template <typename... Args>
    template <std::size_t... INDICES>
    metaxxa_inline void Tuple<Args...>::deallocate(unsigned char *addr, std::index_sequence<INDICES...>)
    {
        if(data)
        {
            (deallocate<INDICES, typename TypeTuple::template Get<INDICES>>(), ...);
            ::free(addr);
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

#undef ALLOCATE_DATA

#endif // METAXXA_TUPLE_INC