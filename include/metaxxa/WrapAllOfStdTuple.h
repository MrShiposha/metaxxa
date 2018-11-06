#ifndef METAXXA_WRAPALLOFSTDTUPLE_H
#define METAXXA_WRAPALLOFSTDTUPLE_H

#include <tuple>

namespace metaxxa
{
    namespace implementation
    {
        template <typename Tuple, template <typename> typename TemplateClass, size_t INDEX>
        constexpr auto wrap_all_of_std_tuple_types()
        {
            if constexpr (INDEX == std::tuple_size_v<Tuple>)
                return std::tuple<>();
            else
                return std::tuple_cat
                (
                    std::tuple<TemplateClass<std::tuple_element_t<INDEX, Tuple>>>(std::declval<TemplateClass<std::tuple_element_t<INDEX, Tuple>>>()),
                    wrap_all_of_std_tuple_types<Tuple, TemplateClass, INDEX + 1>()
                );
        }
    }

    template <typename Tuple, template <typename> typename TemplateType>
    using WrapAllOfStdTuple = decltype(implementation::wrap_all_of_std_tuple_types<Tuple, TemplateType, 0>());
}

#endif // METAXXA_WRAPALLOFSTDTUPLE_H