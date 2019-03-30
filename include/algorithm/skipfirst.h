#ifndef METAXXA_ALGORITHM_SKIPFIRST_H
#define METAXXA_ALGORITHM_SKIPFIRST_H

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
    using SkipFirst = SeqFilter
    <
        Template,
        TupleT,
        MakeIndexRange<N, std::tuple_size_v<TupleT>>
    >;
}

#endif // METAXXA_ALGORITHM_SKIPFIRST_H