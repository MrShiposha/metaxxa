#ifndef METAXXA_APPLYRESULT_H
#define METAXXA_APPLYRESULT_H

#include <type_traits>

namespace metaxxa
{
    namespace detail
    {
        template <typename Function, typename... Args>
        struct ApplyResult
        {
            using type = std::invoke_result_t<Function, Args...>;
        };

        template <typename Function, typename TupleT, std::size_t... INDICES>
        auto apply_result(std::index_sequence<INDICES...>) 
            -> ApplyResult<Function, std::tuple_element_t<INDICES, TupleT>...>;
    }
    
    template <typename Function, typename TupleT>
    using ApplyResult = typename decltype(detail::apply_result<Function, TupleT>(std::make_index_sequence<std::tuple_size_v<TupleT>>()))::type;
}

#endif // METAXXA_APPLYRESULT_H