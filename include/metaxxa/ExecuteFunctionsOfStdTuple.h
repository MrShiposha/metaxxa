#ifndef METAXXA_EXECUTEFUNCTIONSOFSTDTUPLE_H
#define METAXXA_EXECUTEFUNCTIONSOFSTDTUPLE_H

#include <tuple>
#include <type_traits>

#include "Function.h"

namespace metaxxa
{
    namespace detail
    {   
        template 
        <
            typename Tuple, 
            size_t INDEX, 
            bool IS_ENOUGH, 
            typename... Arguments
        >
        struct Invoker
        {
            template <typename ResultTuple>
            auto operator()(const Tuple &functions, ResultTuple &&result_tuple, Arguments&&... args)
            {
                using CurrentFunction = std::tuple_element_t<INDEX, Tuple>;

                if constexpr(std::is_invocable_v<CurrentFunction, Arguments...>)
                {
                    if constexpr(std::is_same_v<typename Function<CurrentFunction>::Result, void>)
                    {
                        std::get<INDEX>(functions)(std::forward<Arguments>(args)...);
                        return Invoker<Tuple, INDEX + 1, INDEX + 1 == std::tuple_size_v<Tuple>, Arguments...>()
                        (
                            functions,
                            std::move(result_tuple),
                            std::forward<Arguments>(args)...
                        );
                    }
                    else
                    {
                        return Invoker<Tuple, INDEX + 1, INDEX + 1 == std::tuple_size_v<Tuple>, Arguments...>()
                        (
                            functions,
                            std::tuple_cat
                            (
                                result_tuple,
                                std::make_tuple
                                (
                                    std::get<INDEX>(functions)(std::forward<Arguments>(args)...)
                                )
                            ),
                            std::forward<Arguments>(args)...
                        );
                    }
                }
                else
                    return Invoker<Tuple, INDEX + 1, INDEX + 1 == std::tuple_size_v<Tuple>, Arguments...>()
                    (
                        functions,
                        std::move(result_tuple),
                        std::forward<Arguments>(args)...
                    );
            }
        };

        template 
        <
            typename Tuple, 
            size_t INDEX, 
            typename... Arguments
        >
        struct Invoker<Tuple, INDEX, true, Arguments...>
        {
            template <typename ResultTuple>
            auto operator()(const Tuple &, ResultTuple &&result_tuple, Arguments&&...)
            {
                return result_tuple;
            }
        };
    }

    template <typename Tuple, typename... Arguments>
    auto execute_functions(const Tuple &tuple, Arguments&&...args)
    {
        return detail::Invoker<Tuple, 0, std::tuple_size_v<Tuple> == 0, Arguments...>()
        (
            tuple,
            std::tuple<>(),
            std::forward<Arguments>(args)...
        );
    }
}

#endif //METAXXA_EXECUTEFUNCTIONSOFSTDTUPLE_H