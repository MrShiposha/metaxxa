#ifndef METAXXA_UPPERTYPE_H
#define METAXXA_UPPERTYPE_H

namespace metaxxa
{
    template <typename T>
    struct UpperType
    {
        using Type = typename T::type;
    };
}

#endif // METAXXA_UPPERTYPE_H