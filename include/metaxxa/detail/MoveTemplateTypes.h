#ifndef METAXXA_MOVETEMPLATETYPES_H
#define METAXXA_MOVETEMPLATETYPES_H

namespace metaxxa::detail
{
    template <template <typename...> typename DestTemplate, template <typename...> typename SrcTemplate, typename... Args>
    constexpr auto move_template_types(SrcTemplate<Args...> t) -> DestTemplate<Args...>;    

    template <template <typename...> typename DestTemplate, typename SrcTemplate>
    using MoveTemplateTypes = decltype(move_template_types<DestTemplate>(std::declval<SrcTemplate>()));
}

#endif // METAXXA_MOVETEMPLATETYPES_H