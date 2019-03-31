#ifndef METAXXA_ALGORITHM_SKIPLAST_H
#define METAXXA_ALGORITHM_SKIPLAST_H

#include <type_traits>

#include "seqfilter.h"
#include "../indexrange.h"

namespace metaxxa
{
    template
    <
        template <typename...> typename Template,
        typename TupleT,
        std::size_t N
    >
    using SkipLast = SeqFilter
    <
        Template,
        TupleT,
        MakeIndexRange<0, std::tuple_size_v<TupleT> - N>
    >;
}

#endif // METAXXA_ALGORITHM_SKIPLAST_H