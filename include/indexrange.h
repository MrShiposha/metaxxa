#ifndef METAXXA_INDEXRANGE_H
#define METAXXA_INDEXRANGE_H

#include <utility>

namespace metaxxa
{
    namespace detail
    {
        template <std::size_t TO_ADD, std::size_t... SEQ>
        constexpr auto shift_seq(std::index_sequence<SEQ...> &&)
            -> std::index_sequence<TO_ADD + SEQ ...>;
    }

    template <std::size_t MIN, std::size_t MAX>
    using MakeIndexRange = decltype(detail::shift_seq<MIN>(std::declval<std::make_index_sequence<MAX-MIN>>())); 
}

#endif // METAXXA_INDEXRANGE_H