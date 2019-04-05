#ifndef METAXXA_ALGORITHM_TAKEFIRST_H
#define METAXXA_ALGORITHM_TAKEFIRST_H

#include "takerange.h"

namespace metaxxa
{
    template
    <
        template <typename...> typename Template,
        typename TupleT,
        std::size_t N
    >
    using TakeFirst = TakeRange
    <
        Template,
        TupleT,
        0, N
    >;
}

#endif // METAXXA_ALGORITHM_TAKEFIRST_H