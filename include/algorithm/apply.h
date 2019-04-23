#ifndef METAXXA_ALGORITHM_APPLY_H
#define METAXXA_ALGORITHM_APPLY_H

namespace metaxxa
{
    template <typename Function, typename Tuple>
    constexpr auto apply(Function &&, Tuple &&); 
}

#endif // METAXXA_ALGORITHM_APPLY_H