#ifndef METAXXA_TYPEIF_H
#define METAXXA_TYPEIF_H

#include <type_traits>

#include "if.h"

namespace metaxxa
{
    template <typename T>
    using TypeIf = If<!std::is_same_v<T, std::false_type>>;
}

#endif // METAXXA_TYPEIF_H