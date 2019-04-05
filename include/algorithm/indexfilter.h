#ifndef METAXXA_ALGORITHM_INDEXFILTER_H
#define METAXXA_ALGORITHM_INDEXFILTER_H

#include <type_traits>

namespace metaxxa
{
    template 
    <
        template <typename...> typename Template, 
        typename TupleT, 
        std::size_t... INDICES
    >
    using IndexFilter = Template<std::tuple_element_t<INDICES, TupleT>...>;
}

#endif // METAXXA_ALGORITHM_INDEXFILTER_H