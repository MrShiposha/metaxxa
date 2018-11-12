#ifndef METAXXA_FILTEROFSTDTUPLE_H
#define METAXXA_FILTEROFSTDTUPLE_H

#include <tuple>
#include <type_traits>

#include "WrapOfStdTuple.h"

namespace metaxxa
{
    namespace detail
    {
        template <typename TupleOfOptionals, typename Tuple, typename Callable, size_t INDEX>
        constexpr auto filter(TupleOfOptionals &tuple_of_optionals, Tuple &tuple, Callable &callable)
        {
            if constexpr (INDEX == std::tuple_size_v<TupleOfOptionals>)
                return tuple_of_optionals;
            else
            {
                {
                    auto &element = std::get<INDEX>(tuple);
                    if (callable(element))
                        std::get<INDEX>(tuple_of_optionals) = element; 
                }

                return filter<TupleOfOptionals, Tuple, Callable, INDEX + 1>(tuple_of_optionals, tuple, callable);
            }
        }

        template 
        <
            typename Tuple, 
            template <typename ValueType> typename Functor,
            size_t INDEX,
            typename... FunctorArguments
        >
        constexpr auto filter_types(FunctorArguments&&... arguments)
        {
            if constexpr (INDEX + 1 == std::tuple_size_v<Tuple>)
                return std::tuple<>();
            else
            {
                using FunctorInstance = Functor<std::tuple_element_t<INDEX, Tuple>>;

                static_assert
                (
                    Type<FunctorInstance>::template has_operator_call<bool()>(),
                    "metaxxa static error:  Functor has no non-const 'bool operator()()'"
                );

                FunctorInstance checker(std::forward<FunctorArguments>(arguments)...);

                if constexpr (checker())
                    return std::declval
                    <
                        decltype
                        (
                            std::tuple_cat
                            (   
                                std::make_tuple(std::declval<std::tuple_element_t<INDEX, Tuple>>()),
                                filter_types<Tuple, Functor, INDEX + 1, FunctorArguments...>(std::forward<FunctorArguments>(arguments)...)
                            )
                        )
                    >();
                else
                    return std::declval<decltype(filter_types<Tuple, Functor, INDEX + 1, FunctorArguments...>(std::forward<FunctorArguments>(arguments)...))>();
            }
        }
    }

    template <typename Tuple, typename Callable>
    constexpr auto filter(Tuple &tuple, Callable &callable)
    {
        using TupleOfOptionals = decltype(wrap_of_std_tuple_types<Tuple, METAXXA_OPTIONAL>());
        TupleOfOptionals tuple_of_optionals;

        return detail::filter<TupleOfOptionals, Tuple, Callable, 0>(tuple_of_optionals, tuple, callable);
    }

    template 
    <
        typename Tuple, 
        template <typename ValueType> typename Functor,
        typename... FunctorArguments
    >
    constexpr auto filter_types(FunctorArguments&&... arguments)
    {
        return detail::filter_types<Tuple, Functor, 0, FunctorArguments...>(std::forward<FunctorArguments>(arguments)...);
    }

}

#endif // METAXXA_FILTEROFSTDTUPLE_H