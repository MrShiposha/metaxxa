#ifndef METAXXA_detail_ARGUMENTSSIGNATUREBUILDER_H
#define METAXXA_detail_ARGUMENTSSIGNATUREBUILDER_H

#include <string>

namespace metaxxa::detail
{
    template <typename ArgumentType>
    struct ArgumentsSignatureBuilder
    {
        ArgumentsSignatureBuilder(std::string &result);

        void operator()();

    private:
        std::string &result;
    };
}

#endif // METAXXA_detail_ARGUMENTSSIGNATUREBUILDER_H