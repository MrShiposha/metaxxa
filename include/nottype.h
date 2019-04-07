#ifndef METAXXA_NOTTYPE_H
#define METAXXA_NOTTYPE_H

namespace metaxxa
{
    struct NotType
    {};

    static inline constexpr NotType NOTTYPE;
}

namespace std
{
    template <std::size_t INDEX>
    class tuple_element<INDEX, metaxxa::NotType>
    {
    public:
        using type = metaxxa::NotType;
    };

    template <>
    class tuple_size<metaxxa::NotType>
    {
    public:
        static constexpr std::size_t value = 0;
    };

    template <std::size_t INDEX>
    auto get(const metaxxa::NotType &)
    {
        return metaxxa::NOTTYPE;
    }
}

#endif // METAXXA_NOTTYPE_H