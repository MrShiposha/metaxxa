#ifndef METAXXA_WRAPALLOFSTDTUPLE_H
#define METAXXA_WRAPALLOFSTDTUPLE_H

#include <tuple>

namespace metaxxa
{
    namespace implementation
    {
        template <template <typename> typename TemplateType, typename... Types>
        using WrapAllOfStdTuple = std::tuple<TemplateType<Types>...>;

        template <template <typename> typename TemplateType, typename... Types>
        constexpr auto wrap_all_of_std_tuple(const std::tuple<Types...> &) -> WrapAllOfStdTuple<TemplateType, Types...>;
    }

    template <typename Tuple, template <typename> typename TemplateType>
    using WrapAllOfStdTuple = decltype(implementation::wrap_all_of_std_tuple<TemplateType>(std::declval<Tuple>()));
}

#endif // METAXXA_WRAPALLOFSTDTUPLE_H