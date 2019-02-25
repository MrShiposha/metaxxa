#ifndef METAXXA_detail_ARGUMENTSSIGNATUREBUILDER_INC
#define METAXXA_detail_ARGUMENTSSIGNATUREBUILDER_INC

#include "ArgumentsSignatureBuilder.h"
#include "../Type.h"

namespace metaxxa::detail
{
    template <typename T>
    ArgumentsSignatureBuilder<T>::ArgumentsSignatureBuilder(std::string &result)
    : result(result)
    {}

    template <typename T>
    void ArgumentsSignatureBuilder<T>::operator()()
    {
        if (!result.empty())
            result += ", ";
        result += Type<T>::name_with_modifiers();
    }
}


#endif // METAXXA_detail_ARGUMENTSSIGNATUREBUILDER_INC