#ifndef METAXXA_SIZECONSTANT_H
#define METAXXA_SIZECONSTANT_H

#include <type_traits>

#include "uppervalue.h"

namespace metaxxa
{
    template <std::size_t INDEX>
    using SizeConstant = UpperValue<std::integral_constant<std::size_t, INDEX>>;
}

#endif // METAXXA_SIZECONSTANT_H