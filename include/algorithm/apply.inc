#ifndef METAXXA_ALGORITHM_APPLY_INC
#define METAXXA_ALGORITHM_APPLY_INC

#include <functional>

namespace metaxxa
{
    namespace detail
    {
        template <typename Callable, typename Tuple, std::size_t... INDICES>
        auto apply(Callable &&function, Tuple &&tuple, std::index_sequence<INDICES...>)
        {
            return std::invoke
            (
                std::forward<Callable>(function), 
                std::forward<std::tuple_element_t<INDICES, std::decay_t<Tuple>>>(std::get<INDICES>(tuple))...
            );
        }
    }

    template <typename Function, typename Tuple>
    constexpr auto apply(Function &&function, Tuple &&tuple)
    {
        return detail::apply
        (
            std::forward<Function>(function), 
            std::forward<Tuple>(tuple), 
            std::make_index_sequence<std::tuple_size_v<std::decay_t<Tuple>>>()
        );
    }
}

#endif // METAXXA_ALGORITHM_APPLY_INC