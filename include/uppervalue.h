#ifndef METAXXA_UPPERVALUE_H
#define METAXXA_UPPERVALUE_H

namespace metaxxa
{
    template <typename T>
    struct UpperValue
    {
        using Type = typename T::value_type;

        static constexpr Type VALUE = T::value;
    };
}

#endif // METAXXA_UPPERVALUE_H