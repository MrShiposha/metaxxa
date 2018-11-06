#ifndef METAXXA_DISTINCTOFSTDTUPLE_H
#define METAXXA_DISTINCTOFSTDTUPLE_H

#include <tuple>

#include "ContainsOfStdTuple.h"
#include "detail/MoveTemplateTypes.h"

namespace metaxxa
{
    namespace detail
    {
        template <typename SrcTuple, typename DistinctTuple, size_t INDEX>
        constexpr auto distinct_types()
        {
            using ConcatTuple = decltype(std::tuple_cat(std::declval<DistinctTuple>(), std::declval<std::tuple<std::tuple_element_t<INDEX, SrcTuple>>>())); 

            if constexpr (INDEX + 1 == std::tuple_size_v<SrcTuple> && !::metaxxa::contains_types<DistinctTuple, std::tuple_element_t<INDEX, SrcTuple>>())
                return std::declval<ConcatTuple>();
            else if constexpr (INDEX + 1 == std::tuple_size_v<SrcTuple>)
                return std::declval<DistinctTuple>();
            else if constexpr (!::metaxxa::contains_types<DistinctTuple, std::tuple_element_t<INDEX, SrcTuple>>())
                return distinct_types<SrcTuple, ConcatTuple, INDEX + 1>();
            else
                return distinct_types<SrcTuple, DistinctTuple, INDEX + 1>();
        }
    }

    template <typename Tuple>
    constexpr auto distinct_types(std::enable_if_t<!std::is_same_v<Tuple, std::tuple<>>> * = nullptr)
    {
        return detail::distinct_types<Tuple, std::tuple<>, 0>();
    }

    template <typename Tuple>
    constexpr auto distinct_types(std::enable_if_t<std::is_same_v<Tuple, std::tuple<>>> * = nullptr)
    {
        return std::tuple<>();
    }
}

#endif // METAXXA_DISTINCTOFSTDTUPLE_H