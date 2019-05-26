#ifndef METAXXA_ISARRAYOF_H
#define METAXXA_ISARRAYOF_H

#include <type_traits>

namespace metaxxa
{
    template <typename T, typename Of>
    constexpr bool is_array_of()
    {
        using TNCV = std::remove_cv_t<std::remove_reference_t<T>>;
        using OfNCV = std::remove_cv_t<std::remove_reference_t<Of>>;

        return std::is_array_v<TNCV> 
        && std::is_same_v
        <
            TNCV, 
            OfNCV[std::extent_v<TNCV>]
        >;
    }    
}

#endif // METAXXA_ISARRAYOF_H